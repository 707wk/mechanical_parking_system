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
<h3>【权限管理】</h3>
<div style="max-width:800px">
 <table  id="table1"  data-undefined-text="无" data-pagination="true"  data-search="true"data-show-refresh="true"  data-page-list="[10,50, 100, 200, ALL]" data-toolbar="#toolbar1" >
</table>
</div>
<div id="toolbar1" class="btn-group">
<button class="btn btn-primary" onclick="add()"><span class="glyphicon glyphicon-pencil" aria-hidden="true"></span>&nbsp;添加</button>&nbsp;
<button class="btn btn-primary" onclick="edit()"><span class="glyphicon glyphicon-pencil" aria-hidden="true"></span>&nbsp;编辑</button>&nbsp;
<button class="btn btn-primary" onclick="del()"><span class="glyphicon glyphicon-remove" aria-hidden="true"></span>&nbsp;删除</button>	
</div>
<div class="modal-dialog " id="edit" style="display:none; width: 350px;margin-left:30%;margin-top:-80px;;">
	<div class="modal-content">
		<div class="modal-header">
			<button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">×</span><span class="sr-only">Close</span></button>
			<h4 class="modal-title">权限管理</h4>
		</div>
		<div class="modal-body" style="height:120px;" style="width:180px;">
				<div style="">
					<label>用户名</label>
					<input type="text" class="form-control" id="name" placeholder="" style="width:180px;"><br>
					<label>权　限</label>
					<select id="type"  class="form-control" style="width:180px;">
						<option value="1">超级管理员</option>
						<option value="2">管理员</option>
						<option value="3">来宾</option>
					</select><br>
					<label>密　码</label>
					<input type="text" class="form-control" id="pwd" placeholder="留空则不修改" style="width:180px;">
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

<div class="modal-dialog " id="add" style="display:none; width: 350px;margin-left:30%;margin-top:-80px;;">
	<div class="modal-content">
		<div class="modal-header">
			<button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">×</span><span class="sr-only">Close</span></button>
			<h4 class="modal-title">添加管理员用户</h4>
		</div>
		<div class="modal-body" style="height:120px;">
				<div style="">
					<label>用户名</label>
					<input type="text" class="form-control" id="name1" placeholder="" style="width:180px;"><br>
					<label>权　限</label>
					<select id="type1"  class="form-control" style="width:180px;">
						<option value="1">超级管理员</option>
						<option value="2">管理员</option>
						<option value="3">来宾</option>
					</select>
					<br>
					<label>密　码</label>
					<input type="text" class="form-control" id="pwd1" placeholder="" style="width:180px;">
				</div>
		</div>
		<div class="modal-footer">
			<center>
				<button type="button" class="btn btn-primary" data-dismiss="modal" onclick="addsubmit()">添加</button>　
				<button type="button" class="btn btn-default" data-dismiss="modal">取消</button>　
			</center>
		</div>
	</div>
</div>
<script>
function init(){
$('#table1').bootstrapTable({
				url: 'ajaxapi.php?cmd=userper',
				striped: true,        
				clickToSelect:true,
				singleSelect:true,
				columns: [
				{
					field: 'ra1',
					checkbox: true
				},
				{
					field: 'name',
					title: '用户名'
				}, 
				{
					field: 'type',
					title: '权限'
				}
				/*, {
					field: 'type',
					title: '类型'
				},*/ ]
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
	$('#name').val(row.name);
	$('#type').val(row.type);
	$("#edit").modal("toggle"); 
	
}
function add(){
	$("#add").modal("toggle"); 
	
}

function addsubmit(){
	$.ajax({
		type:"GET",url:"ajaxapi.php",
		data:{cmd:'addadminuser',name:$('#name1').val(),type:$('#type1').val(),pwd:$('#pwd1').val()},
		success:function(data){
			var zt=JSON.parse(data);
			alert(zt.msg);
			if(zt.code){
				$('#table1').bootstrapTable('refresh');
			}
		}});

}

function editsubmit(){
	$.ajax({
		type:"GET",url:"ajaxapi.php",
		data:{cmd:'editadminuser',name:$('#name').val(),type:$('#type').val(),pwd:$('#pwd').val()},
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
		data:{cmd:'deladminuser',name:rows[0].name},
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