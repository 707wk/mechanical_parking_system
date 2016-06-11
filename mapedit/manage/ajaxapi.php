<?php
/*************************************
 *CREATED :2016/5/05
 *TEXT    :API
 *EMAIL   :dksx@qq.com
 *************************************/
 require_once "main.php";
 $cmd=@$_GET['cmd'];
 switch($cmd){
	case "carstate":
		$arr=$dbh->query("SELECT * FROM `t_carinfo` WHERE 1")->fetchAll();
		echo json_encode($arr);
		break;
	case "yhlb":
		$arr=$dbh->query("SELECT * FROM `t_car_user` WHERE 1")->fetchAll();
		echo json_encode($arr);
		break;
		
 }