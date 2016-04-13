<?php
//配置文件
$config=array(
	'sqlhost'=>'localhost',
	'sqluser'=>'car',
	'sqlpwd'=>'KnKsfyxX65dMVWKY',
	'dbname'=>'car',
);
$dbh=null;
try
{
	$dbh = new PDO("mysql:host=localhost;dbname=car","car","KnKsfyxX65dMVWKY",
	array(PDO::ATTR_PERSISTENT => true)); 
    $dbh->query("set names utf8");
}
catch (PDOException $e)
{
	echo 'Connection failed: ' . $e->getMessage();
	die;
}