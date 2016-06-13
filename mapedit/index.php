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
			$_SESSION['user']=@$_POST['phone'];
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
		$result=$dbh->prepare("SELECT `phone`,`plate`, `money` FROM `t_car_user` WHERE phone=?");
		$sth=$result->execute(array($_SESSION['user']));
		if($result->rowCount()==1){
			$info=$result->fetch();
			exit(json_encode(array('code'=>1,"msg"=>"success","info"=>$info,"token"=>session_id())));
		}
		else {
			exit(json_encode(array('code'=>0,"msg"=>"手机号或密码错误!")));
		}
	case "reserve":
		exit(json_encode(array('code'=>1,"msg"=>"预约成功","savetime"=>date("Y-m-d H:i:s",strtotime("+140 min")),"token"=>session_id())));
	case "cancel_reserve":
		exit(json_encode(array('code'=>1,"msg"=>"取消预约成功","token"=>session_id())));
	case "getfreecarport":
		exit(json_encode(array('code'=>1,"msg"=>rand(0,20),"token"=>session_id())));
	case "gethistory":
		if(empty($_SESSION['user']))exit(json_encode(array('code'=>0,"msg"=>"身份已过期,请重新登陆!")));
		$result=$dbh->prepare("SELECT * FROM `t_history` WHERE 1 order by time");
		$sth=$result->execute(array($_SESSION['user']));
		$info=$result->fetchAll();
		exit(json_encode(array('code'=>1,"msg"=>"success","data"=>$info,"token"=>session_id())));
	
	default:
	 echo date("Y-m-d H:i:s",strtotime("+20 min"));
		exit(json_encode(array('code'=>0,"msg"=>"invalid parameter!")));
}