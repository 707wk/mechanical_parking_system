<?php
/*************************************
 *CREATED :2016/4/20
 *TEXT    :立体车库用户管理
 *EMAIL   :dksx@qq.com
 *************************************/
require_once "main.php";
?>
<!DOCTYPE html >
<html >
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>立体车库用户管理</title>
<link href="libs/css/bootstrap.min.css" rel="stylesheet">
<script src="libs/js/jquery.min.js"></script>
<script src="libs/js/bootstrap.min.js"></script>
<link href="libs/css/table.css" rel="stylesheet">
<script src="libs/js/table.js"></script>
<style>
body{
	//background-color: #f5f5f5;
	margin-left:5px;
}
.top{
	text-align:left;
	margin-left:5px;
}
</style>
</head>
<body >
<h3 class="top">【用户管理】</h3>
<div style="max-width:800px">
 <table  id="table1"  data-undefined-text="无" data-pagination="true"  data-search="true"data-show-refresh="true"  data-page-list="[10,50, 100, 200, ALL]" data-toolbar="#toolbar1" >
</table>
</div>
<div id="toolbar1">
<button class="btn btn-success" onclick="alert('building...')">增加用户</button>&nbsp;
<button class="btn btn-info" onclick="alert('building...')">编辑用户</button>&nbsp;
<button class="btn btn-danger" onclick="alert('building...')">删除用户</button>	
</div>
<script>
function init(){
$('#table1').bootstrapTable({
				url: 'userapi.php?cmd=yhlb',
				columns: [
				{
					field: 'ra1',
					checkbox: true
				},
				{
					field: 'id',
					title: 'ID'
				}, 
				{
					field: 'name',
					title: '用户名'
				}, {
					field: 'type',
					title: '类型'
				}, ]
			});
}
init();
</script>
</body>