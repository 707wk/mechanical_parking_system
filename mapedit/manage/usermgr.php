<?php
/*************************************
 *CREATED :2016/4/20
 *TEXT    :立体车库用户管理
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
.form-control{
	width:auto;
	display:inline;
}
</style>
</head>
<body >
<h3>【用户管理】</h3>
<div style="max-width:800px">
 <table  id="table1"  data-undefined-text="无" data-pagination="true"  data-search="true"data-show-refresh="true"  data-page-list="[10,50, 100, 200, ALL]" data-toolbar="#toolbar1" >
</table>
</div>
<div id="toolbar1" class="btn-group">
<button class="btn btn-primary" onclick="edit()"><span class="glyphicon glyphicon-pencil" ></span>&nbsp;编辑</button>&nbsp;
<button class="btn btn-primary" onclick="del()"><span class="glyphicon glyphicon-remove" ></span>&nbsp;删除</button>	
</div>
<div class="modal-dialog " id="edit" style="display:none; width: 350px;margin-left:30%;margin-top:-80px;;">
	<div class="modal-content">
		<div class="modal-header">
			<button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">×</span><span class="sr-only">Close</span></button>
			<h4 class="modal-title">编辑用户信息</h4>
		</div>
		<div class="modal-body" style="height:120px;">
				<div style="">
					<label>手机号</label>
					<input type="text" class="form-control" id="phone" readonly="true" placeholder=""><br>
					<label>车牌号</label>
					<input type="text" class="form-control" id="plate" placeholder=""><br>
					<label>余　额</label>
					<input type="text" class="form-control" id="money" placeholder=""><br>
					<label>密　码</label>
					<input type="text" class="form-control" id="pwd" placeholder="留空则不修改">
				</div>
		</div>
		<div class="modal-footer">
			<center>
				<button type="button" class="btn btn-primary" data-dismiss="modal" onclick="editsubmit()">保存</button>　
				<button type="button" class="btn btn-default" data-dismiss="modal">放弃修改</button>　
			</center>
		</div>
	</div>
</div>
<script>
function init(){
$('#table1').bootstrapTable({
				url: 'ajaxapi.php?cmd=yhlb',
				clickToSelect:true,
				singleSelect:true,
				columns: [
				{
					field: 'ra1',
					checkbox: true
				},
				{
					field: 'phone',
					title: '手机号'
				}, 
				{
					field: 'plate',
					title: '车牌号'
				},
				{
					field: 'money',
					title: '余额'
				},]
			});
}
init();
function getrow() {return $.map($('#table1').bootstrapTable('getSelections'), function (row) { return row});}
function edit(){
	var rows=getrow();
	if(rows.length!=1){
	alert('没有选择项!');
	return ;
}
	var row=rows[0];
	$('#phone').val(row.phone);
	$('#plate').val(row.plate);
	$('#money').val(row.money);
	
	$("#edit").modal("toggle"); 
	
}
function editsubmit(){
	$.ajax({
		type:"GET",url:"ajaxapi.php",
		data:{cmd:'edituser',phone:$('#phone').val(),plate:$('#plate').val(),pwd:$('#pwd').val(),money:$('#money').val()},
		success:function(data){
			var zt=JSON.parse(data);
			alert(zt.msg);
			if(zt.code){
				$('#table1').bootstrapTable('refresh');
			}
		}});

}
function del(){
	var rows=getrow();
	$.ajax({
		type:"GET",url:"ajaxapi.php",
		data:{cmd:'deluser',phone:rows[0].phone},
		success:function(data){
			var zt=JSON.parse(data);
			alert(zt.msg);
			if(zt.code){
				$('#table1').bootstrapTable('refresh');
			}
		}});
}
</script>
</body>