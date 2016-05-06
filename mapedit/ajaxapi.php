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
		$arr=$dbh->query("SELECT t_carinfo.plate,`carbarnid`, `num`, `rows`, `cols`,`start`,`end` FROM `t_carinfo`,`t_carlocation` WHERE t_carinfo.plate=t_carlocation.plate")->fetchAll();
		echo json_encode($arr);
		break;
	case "yhlb":
		break;
		
 }