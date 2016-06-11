<?php 
/*************************************
 *CREATED :2016/5/05
 *TEXT    :车辆状态
 *EMAIL   :dksx@qq.com
 *************************************/
 require_once "main.php";
?>
<!DOCTYPE html >
<html >
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>state</title>
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
#carsearch{
	width:196px;
	margin-right:0px;
	display: inline;
}
#toolbar{
	//text-align:right;
}
table{
	background-color: #FFF;
}
</style>
</head>
<body >
<h3>【历史记录】</h3>
<div style="max-width:800px">
 <div id="toolbar1" style="margin-left:100px;">
 </div>
 <table  id="table1"  data-undefined-text="无" data-pagination="true"  data-search="true"data-show-refresh="true"  data-page-list="[10,50, 100, 200, ALL]" data-toolbar="#toolbar1" >
</table>
</div>

<script>
function init(){
$('#table1').bootstrapTable({
				url: 'ajaxapi.php?cmd=carstate',
				striped: true,        
				columns: [
				/*{
					field: 'ra1',
					checkbox: true
				},
				*/
				{
					field: 'plate',
					title: '车辆编号'
				},
				{
					field: 'carbarnid',
					title: '模块编号'
				}, 
				{
					field: 'num',
					title: '存储位置编号'
				} ]
			});
		$('#toolbar1').css("margin-left",parseInt($('#table1').css('width'))-239+"px");
}
init();
	

</script>
</body>