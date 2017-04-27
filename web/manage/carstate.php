<?php 
/*************************************
 *CREATED :2016/5/05
 *TEXT    :车辆状态
 *EMAIL   :dksx@qq.com
 *************************************/
 require_once "main.php";
  needLogin();
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
<h3>【车辆状态】</h3>
<div style="max-width:800px">
 <div id="toolbar1" style="margin-left:100px;">
 <input type="text" class="form-control" id="carsearch" placeholder="按车辆编号搜索">
 <button class="btn btn-default" type="button" id="refresh" title="刷新"><i class="glyphicon glyphicon-refresh icon-refresh"></i></button>
 </div>
 <table  id="table1"  data-undefined-text="无" data-pagination="true"  data-search="false"data-show-refresh="false"  data-page-list="[10,50, 100, 200, ALL]" data-toolbar="#toolbar1" >
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
				}, {
					field: 'rows',
					title: '层数'
				},{
					field: 'cols',
					title: '列数'
				},{
					field: 'start',
					title: '存车开始时间'
				} ]
			});
		$('#toolbar1').css("margin-left",parseInt($('#table1').css('width'))-239+"px");
}
init();
$("#carsearch").keyup(function(){
	var plt=$('#carsearch').val();
	if(plt)$('#table1').bootstrapTable('filterBy',{'plate':plt});
	else $('#table1').bootstrapTable('filterBy',null);
});	
$("#refresh").click(function(){
	$('#table1').bootstrapTable('refresh');
});	

</script>
</body>