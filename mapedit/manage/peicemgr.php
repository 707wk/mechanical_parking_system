<?php
/*************************************
 *CREATED :2016/4/20
 *TEXT    :立体车库收费管理
 *EMAIL   :dksx@qq.com
 *************************************/
require_once "main.php";
 needLogin();
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
	background-color: #F2F2F2;
	margin-left:5px;
}
h3{
	text-align:left;
	margin-left:15px;
}
table{
	background-color: #fff;	
}
</style>
</head>
<body >
<h3>【收费管理】</h3>
<div style="max-width:800px">
 <table  id="table1"  data-undefined-text="无" data-pagination="true"  data-search="true"data-show-refresh="true"  data-page-list="[10,50, 100, 200, ALL]" data-toolbar="#toolbar1" >
</table>
</div>
<script>
function init(){
$('#table1').bootstrapTable({
				url: 'ajaxapi.php?cmd=income',
				striped: true,        
				columns: [
				{
					field: 'ra1',
					checkbox: true
				},
				{
					field: 'time',
					title: '时间'
				}, 
				{
					field: 'money',
					title: '收入'
				}
				/*, {
					field: 'type',
					title: '类型'
				},*/ ]
			});
}
init();
</script>
</body>