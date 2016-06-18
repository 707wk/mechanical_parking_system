<?php
/*************************************
 *CREATED :2016/5/31
 *TEXT    :立体车库客户端API
 *EMAIL   :dksx@qq.com
 *************************************/
require_once "config.php";
date_default_timezone_set('PRC');
$dbh=null;
header("Content-type: text/html; charset=utf-8");
define("INPUTSAVE",0x01);         //入口存车
define("OUTPUTDELE",0x02);         //出口出车
define("OUTPUTGARAGE",0x03);         //车库模块取车
define("RESERVATION",0x04);         //预约存车
define("UNRESERVATION",0x05);         //取消预约
define("GETGARAGEINFO",0x06);         //获取停车场信息
$back_info=array(
1=>"请求成功",
2=>"车位已满",
3=>"无空闲模块",
4=>"未找到车辆",
0xff=>"请求失败");
function sendsock($in){
	global $config;
	$service_port = $config['sockport'];
	$address = $config['sockhost'];
	if(!function_exists("socket_create")){
		error_log(date("y-m-d H:i:s")." 未启用socket模块\n", 3, "error.log");
		return null;
	}
	$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
	if ($socket === false) {
		error_log(date("y-m-d H:i:s")."socket_create() failed, reason: ".socket_strerror(socket_last_error()) . "\n", 3, "error.log");
		return null;
	}
	$result = socket_connect($socket, $address, $service_port);
	if($result === false) {
		error_log(date("y-m-d H:i:s")."socket_connect() failed.\nReason: ($result) " . socket_strerror(socket_last_error($socket)) . "\n", 3, "error.log");
		return null;
	}
	socket_write($socket, $in, strlen($in));
	$result= socket_read($socket, 8192);
	$arr=unpack("C*",$result);
	socket_close($socket);
	return $arr;
}
function getinfo(){
	$in=pack("CC",GETGARAGEINFO,GETGARAGEINFO%128);
	$data=sendsock($in);
	$chewei="";
	$i=3;
	for(;$i<count($data)&&$data[$i]!=32;$i++){
		$chewei.=chr($data[$i]);
	}
	$sysj="";
	for($i++;$i<count($data)&&$data[$i]!=32;$i++){
		$sysj.=chr($data[$i]);
	}
	$chewei=intval($chewei);
	$sysj=intval($sysj);
	// $_SESSION['sycw']=$chewei;
	// $_SESSION['sysj']=$sysj;
	//echo $chewei.$sysj;
	return array($chewei,$sysj);
}
$in=pack("CC",UNRESERVATION,UNRESERVATION%128);
		
		// $data=sendsock($in);
		// var_dump($data);
		// exit();
try
{
	$dbh = new PDO("mysql:host=$config[sqlhost];dbname=$config[dbname]","$config[sqluser]","$config[sqlpwd]"); 
    $dbh->exec("SET NAMES 'utf8'");
	
}
catch (PDOException $e)
{
	echo 'Connection failed: ' . $e->getMessage();
	die;
}
$token=@$_POST['token'];
if(empty($token)){
	Session_start();  
}
else {
	session_id($token);
	Session_start();  
}
switch(@$_POST['type']){
	case "login":
		$result=$dbh->prepare("SELECT `plate`, `money` FROM `t_car_user` WHERE phone=? and passwd=?");
		$result->execute(array(@$_POST['phone'],@$_POST['passwd']));
		if($result->rowCount()==1){
			$arr=$result->fetch();
			$_SESSION['user']=@$_POST['phone'];
			$_SESSION['plate']=$arr['plate'];
			
			exit(json_encode(array('code'=>1,"msg"=>"登陆成功!","token"=>session_id())));
		}
		else {
			exit(json_encode(array('code'=>0,"msg"=>"手机号或密码错误!")));
		}
	case "reg":
		$phone=@$_POST['phone'];
		$plate=@$_POST['plate'];
		$md5_pwd=@$_POST['passwd'];
		$result=$dbh->prepare("SELECT `plate`, `money` FROM `t_car_user` WHERE phone=?");
		$result->execute(array($phone));
		if($result->rowCount()==1){
			exit(json_encode(array('code'=>0,"msg"=>"注册失败，该手机号已存在，请找回密码！")));
		}
		$result=$dbh->prepare("INSERT INTO `t_car_user`(`phone`, `passwd`, `plate`, `money`) VALUES (?,?,?,?)");
		$result->execute(array($phone,$md5_pwd,$plate,0));
		if($result){
			exit(json_encode(array('code'=>1,"msg"=>"注册成功，请点击登陆!")));
		}else {
			exit(json_encode(array('code'=>0,"msg"=>"注册失败,未知错误!")));
		}
	case "getinfo":
		if(empty($_SESSION['user']))exit(json_encode(array('code'=>0,"msg"=>"身份已过期,请重新登陆!")));
		$result=$dbh->prepare("SELECT `phone`,`plate`, format(`money`,2) FROM `t_car_user` WHERE phone=?");
		$sth=$result->execute(array($_SESSION['user']));
		if($result->rowCount()==1){
			$info=$result->fetch();
			exit(json_encode(array('code'=>1,"msg"=>"success","info"=>$info,"token"=>session_id())));
		}
		else {
			exit(json_encode(array('code'=>0,"msg"=>"手机号或密码错误!")));
		}
	case "reserve":
		if(empty($_SESSION['plate']))exit(json_encode(array('code'=>0,"msg"=>"预约失败，身份失效","savetime"=>null,"token"=>session_id())));
		$in=pack("CC",RESERVATION,RESERVATION%128);
		$data=sendsock($in);
		if(empty($data)){
			exit(json_encode(array('code'=>0,"msg"=>"预约失败，服务端返回为空","savetime"=>date("Y-m-d H:i:s"),"token"=>session_id())));
		}
		else {
			if($data[1]!=1)exit(json_encode(array('code'=>0,"msg"=>"预约失败，".$back_info[$data[1]],"savetime"=>null,"token"=>session_id())));
			$xx=getinfo();
			$exptime=date("Y-m-d H:i:s",strtotime("+".$xx[1]." min"));
			$sth=$dbh->prepare("INSERT INTO `t_reservation`(`plate`, `endtime`) VALUES ( ? , ? ) ");
			$sth->execute(array($_SESSION['plate'],$exptime));
			exit(json_encode(array('code'=>1,"msg"=>"预约成功","savetime"=>$exptime,"token"=>session_id())));
		}
		// exit(json_encode(array('code'=>1,"msg"=>"预约成功","savetime"=>$exptime,"token"=>session_id())));
	case "cancel_reserve":
		$in=pack("CC",UNRESERVATION,UNRESERVATION%128);
		$data=sendsock($in);
		if($data[1]){
			$sth=$dbh->prepare("DELETE FROM `t_reservation` WHERE plate=?");
			if($sth->execute(array($_SESSION['plate']))) exit(json_encode(array('code'=>1,"msg"=>"取消预约成功","token"=>session_id())));
		}
		//var_dump($data);
		exit(json_encode(array('code'=>0,"msg"=>"取消预约失败","token"=>session_id())));
	case "getfreecarport":
		$sth=$dbh->prepare("SELECT endtime from `t_reservation` where plate=?");
		$sth->execute(array($_SESSION['plate']));
		if($sth->rowCount()>0){
			$row=$sth->fetch();
			exit(json_encode(array('code'=>2,"savetime"=>$row['endtime'],"token"=>session_id())));
		}
		else {
			getinfo();
			$xx=getinfo();
			exit(json_encode(array('code'=>1,"msg"=>$xx[0],"token"=>session_id())));
		}
	case "gethistory":
		if(empty($_SESSION['user']))exit(json_encode(array('code'=>0,"msg"=>"身份已过期,请重新登陆!")));
		$result=$dbh->prepare("SELECT * FROM `t_history` WHERE plate=? order by time");
		$sth=$result->execute(array($_SESSION['plate']));
		$info=$result->fetchAll();
		exit(json_encode(array('code'=>1,"msg"=>"success","data"=>$info,"token"=>session_id())));
	
	default:
	 //echo date("Y-m-d H:i:s",strtotime("+20 min"));
		exit(json_encode(array('code'=>0,"msg"=>"invalid parameter!")));
}