<?php
/*************************************
 *CREATED :2016/3/31
 *TEXT    :立体车库管理后台全局文件
 *EMAIL   :dksx@qq.com
 *************************************/

require_once "../config.php";
session_start();
$dbh=null;
try
{
	$dbh = new PDO("mysql:host=$config[sqlhost];dbname=$config[dbname]","$config[sqluser]","$config[sqlpwd]",array(PDO::ATTR_PERSISTENT => true)); 
    $dbh->query("set names utf8");
}
catch (PDOException $e)
{
	echo 'Connection failed: ' . $e->getMessage();
	die;
}
function needLogin(){
	if($_SESSION['auth']!=1){
		header("Location:login.php");
		exit(json_encode(array("code"=>0,"msg"=>"身份已过期!")));
	}
}
