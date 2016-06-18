<?php
/*************************************
 *CREATED :2016/5/05
 *TEXT    :API
 *EMAIL   :dksx@qq.com
 *************************************/
 require_once "main.php";
 $cmd=@$_GET['cmd'];
 if($cmd=="login"){
	 $result=$dbh->prepare("SELECT `type` FROM `t_user` WHERE name=? and password=?");
	 $result->execute(array(@$_GET['name'],@$_GET['pwd']));
	 if($result->rowCount()>0){
		$_SESSION['auth']=1;
		exit(json_encode(array("code"=>1,"msg"=>"登陆成功!")));
	}
	exit(json_encode(array("code"=>0,"msg"=>"用户名或密码错误!")));
 }

 needLogin();
 switch($cmd){
	case "carstate":
		$arr=$dbh->query("SELECT * FROM `t_carinfo` WHERE 1")->fetchAll();
		echo json_encode($arr);
		break;
	case "yhlb":
		$arr=$dbh->query("SELECT * FROM `t_car_user` WHERE 1")->fetchAll();
		echo json_encode($arr);
		break;
	case "userper":
		$arr=$dbh->query("SELECT * FROM `t_user` WHERE 1")->fetchAll();
		echo json_encode($arr);
		break;
	case "income" :
		$arr=$dbh->query("SELECT `time`, `money` FROM `t_history` WHERE  `timestatus`=1")->fetchAll();
		echo json_encode($arr);
		break;
	case "edituser":
		$phone=@$_GET['phone'];
		$plate=@$_GET['plate'];
		$money=@$_GET['money'];
		$pwd=@$_GET['pwd'];
		$zt=false;
		if(empty($pwd)){
			$result=$dbh->prepare("UPDATE `t_car_user` SET `plate`=?,`money`=? WHERE phone=?");
			$zt=!!$result->execute(array($plate,$money,$phone));
		}
		else {
			$result=$dbh->prepare("UPDATE `t_car_user` SET `plate`=?,`money`=?,pwd=md5(?) WHERE phone=?");
			$zt=!!$result->execute(array($plate,$money,$pwd,$phone));
		}
		echo json_encode(array("code"=>$zt,"msg"=>$zt?"修改成功":"修改失败"));
		break;
	case "deluser":
		$phone=@$_GET['phone'];
		$result=$dbh->prepare("DELETE FROM `t_car_user` WHERE phone=?");
		$zt=!!$result->execute(array($phone));
		echo json_encode(array("code"=>$zt,"msg"=>$zt?"删除成功":"删除失败"));
		break;
	case "editadminuser":
		$name=@$_GET['name'];
		$type=@$_GET['type'];
		$pwd=@$_GET['pwd'];
		$zt=false;
		if(empty($pwd)){
			$result=$dbh->prepare("UPDATE `t_user` SET `type`=? WHERE name=?");
			$zt=!!$result->execute(array($type,$name));
		}
		else {
			$result=$dbh->prepare("UPDATE `t_user` SET type=?,pwd=md5(?) WHERE name=?");
			$zt=!!$result->execute(array($type,$pwd,$name));
		}
		echo json_encode(array("code"=>$zt,"msg"=>$zt?"修改成功":"修改失败"));
		break;
	case "deladminuser":
		$name=@$_GET['name'];
		$result=$dbh->prepare("DELETE FROM `t_user` WHERE name=?");
		$zt=!!$result->execute(array($name));
		echo json_encode(array("code"=>$zt,"msg"=>$zt?"删除成功":"删除失败"));
		break;
	case "addadminuser":
		$name=@$_GET['name'];
		$type=@$_GET['type'];
		$pwd=@$_GET['pwd'];
		$result=$dbh->prepare("INSERT INTO `t_user`(`name`, `password`, `type`) VALUES (?,md5(?),?)");
		$zt=!!$result->execute(array($name,$pwd,$type));
		echo json_encode(array("code"=>$zt,"msg"=>$zt?"添加成功":"添加失败"));
		break;
 }
 
 
 
 
 
 
 
 
 
 
 
 
 