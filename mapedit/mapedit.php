<?php
/*************************************
 *CREATED :2016/3/21
 *TEXT    :停车场地图管理系统
 *EMAIL   :dksx@qq.com
 *************************************/
require_once "main.php";

switch(@$_GET['do']){
	case "wipemap":
	$dbh->exec('delete from t_map where 1');
	header("Location:mapedit.php");
	exit();
	case 'getmkinfo':
		$result=$dbh->query("select * from t_garageinfo where id=$_GET[mkid]")->fetch();
		echo json_encode($result);
		exit();
	case 'getallmkinfo':
	$result=$dbh->query("select * from t_garageinfo where 1")->fetchAll();
	echo json_encode($result);
	exit();
	case 'getcrkinfo':
	if($dbh->query("select * from t_map where x=$_GET[x] and y=$_GET[y]")->rowCount()==0){
		$dbh->exec("INSERT INTO `t_map`( `x`, `y`, `type`, `type_id`) VALUES ($_GET[x] ,$_GET[y] ,$_GET[type] ,0)");
	}
	$result=$dbh->query("select * from t_map where x=$_GET[x] and y=$_GET[y]")->fetch();
	echo json_encode($result);
	exit();	
	
	case 'setmkinfo':
		//mkname  map_queue rows cols speedrows speedcols state
		if($dbh->query("select * from t_map where x=$_GET[x] and y=$_GET[y]")->rowCount()==0)
			$dbh->exec("INSERT INTO `t_map`(`x`, `y`, `type`, `type_id`) VALUES ($_GET[x],$_GET[y],3,$_GET[compotr])");
		else $dbh->exec("UPDATE `t_map` SET `type_id`='$_GET[compotr]',value='',type=3 WHERE x=$_GET[x] and y=$_GET[y]");
		
		if($dbh->query("select * from t_garageinfo where id=$_GET[compotr]")->rowCount()==0){
			$dbh->exec("INSERT INTO `t_garageinfo`(`id`, `name`, `rows`, `cols`, `speedrows`, `speedcols`, `map_queue`) VALUES ('$_GET[compotr]','$_GET[mkid]','$_GET[rows]','$_GET[cols]','$_GET[speedrows]','$_GET[speedcols]','$_GET[map_queue]')  ");
		}
		else {
			$dbh->exec("update t_garageinfo set name='$_GET[mkid]', map_queue='$_GET[map_queue]', rows='$_GET[rows]', cols='$_GET[cols]', speedrows='$_GET[speedrows]', speedcols='$_GET[speedcols]',id='$_GET[compotr]' where id=$_GET[compotr]");
		}
		exit('更新成功！');
		
	case 'setcrkinfo':
			if($dbh->exec("UPDATE `t_map` SET `type`=$_GET[type],`type_id`='$_GET[type_id]',`value`='$_GET[value]' WHERE   x=$_GET[x] and y=$_GET[y]"))
				exit('保存成功！');
			exit('保存失败！');
		
}

if(isset($_POST['do'])&&$_POST['y']!=""&&$_POST['x']!=""):
	$x=$_POST['x'];
	$y=$_POST['y'];
	$value=$_POST['value'];
	$type=$_POST['type'];
	if($dbh->query("select id from t_map where x=$x and y=$y")->fetch()){
		$dbh->exec("update t_map set type=$type,type_id='0',value='' where x=$x and y=$y");
	}
	else {
		$dbh->exec("INSERT INTO `t_map`(`x`, `y`, `type`, `type_id`,`value`) VALUES ($x,$y,$type,'0','')");
	}
	if($type==0)$dbh->exec("DELETE FROM `t_map` WHERE type=0");
		header("Location:mapedit.php");
	exit();
endif;

?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
<link href="libs/css/bootstrap.min.css" rel="stylesheet">
<script src="libs/js/jquery.min.js"></script>
<script src="libs/js/bootstrap.min.js"></script>
<title>停车场地图管理系统</title>
<style>
body {
	font-family: '微软雅黑';
	background-color: #fff;
}
input ,select{
	background-color: #fff;
}

.modal_wrapper{
	display: table;
	height: 100%;
	margin: 0px auto;
}
.modal-dialog{
	display: table-cell;
	vertical-align: middle;
}

.mytable td{
	height:22px;
	width:22px;
	border:none;
	font-size:13px;
	color:#fff;
	text-align:center;
	border-radius:1px;
	
}
.wall {
	background:url(img/wall.png)repeat;
}
.road{
	background-color:gainsboro;

}
.mk_in{
	background-color:#b5e61d;
	color:#000;
}
.out{
	background-color:#99d9ea;	
	color:#000;
}
.module{
	background-color:#b97a57;	
	color:#000;
}

#Div0
{
	 position: absolute;
    width: 100%;
    height: 100%;
  float:left; width:auto; 
}
#Div2
{

  float:left; width:auto; 
  width:100px;
   margin-left:20px;
}
#Div1 
{
  margin-left:20px;
  float:right;
}
h3{
	text-align:center;
}
.round {   
	background: #fff none repeat scroll 0 0;
	border: 1px solid #bbb;
	display: inline-block;
	height: 28px;
	margin-top: 2px;
	margin-bottom: 2px;
	margin-right: 2px;
	vertical-align: top;
	width: 100px;
	position: relative;
}
.delquery {   
    background-position: 0 -320px;
    cursor: pointer;
    height: 20px;
    margin: 4px 0px 0 0;
    position: absolute;
    right: 0;
    top: 0;
    width: 20px;
}
.input_key { 
    background: #fff none repeat scroll 0 0;
    border: 0 none;
    border-radius: 0;
    font: 16px/22px arial;
    height: 18px;
    margin: 5px 0 0 5px;
    outline: 0 none;
    padding: 0;
    width: 90px;
    background-repeat: no-repeat;
}

.square { 
	width: 18px; 
	height:18px; 
} 
.bk{
		border:5px solid #aaaaaa;
		border-radius: 5px;-moz-border-radius: 5px;-webkit-border-radius: 5px;
}
.top{
	text-align:left;
	margin-left:20px;
}
.form-control{
	margin-right:0px;display:inline;width:auto;
}
.modal{
	margin:5% 10% 5% 10%;overflow-x:hidden;overflow-y:hidden;
}
</style>
</head>
<body>

<div id="Div0">
<h3 class="top">【地图设置】</h3>
<div id="Div1">
<div class="bk">
<table style="font-size:12px;margin-bottom:-16px">
	<tr>
	<td  ></td> <td>　</td>
		<td class="square mk_in" ></td> <td>入口　</td>
		<td class="square out"></td> <td>出口　</td>
		<td class="square module"></td> <td>车库模块</td>
	</tr>
</table>　
<?php 

function create(){
	global $dbh;
	$arr=$dbh->query("select * from t_map ")->fetchAll();
	//var_dump($arr);
	$maxx=$maxy=0;
	$map;
	foreach($arr as $a){
		$type=$a['type'];
		$type=array(0=>'wall','mk_in','out','module','road');
		$map[$a['x']][$a['y']]=array('t'=>$a['type'],'type'=>$type[$a['type']],'value'=>$a['type_id']?$a['type_id']:'');		
		if($a['x']>$maxx)$maxx=$a['x'];
		if($a['y']>$maxy)$maxy=$a['y'];
	}
	echo '<table class="mytable" style="background-color:#000;;" border="0" cellpadding="0" cellspacing="0">'."\n";
	for($i=0;$i<=$maxx+1;$i++){
		for($j=0;$j<=$maxy+1;$j++){ 
			$class="wall";$value="";$t="0";
			if(!empty($map[$i][$j])){
				$class=$map[$i][$j]['type'];
				$value=$map[$i][$j]['value'];
				$t=$map[$i][$j]['t'];
			}
			echo "<td class=\"{$class}\" onclick=\"edit({$i},{$j},{$t},'{$value}');\" id=\"{$i}_{$j}\" onmousedown=\"this.style.opacity='0.5';\" onmousemove=\"this.style.opacity='1';\" onmouseup=\"this.style.opacity='1';\">{$value}</td>\n";	
		}
		echo "</tr>";
	}
	echo "</table></div>";

}

function init(){
	global $dbh;
	//var_dump( );
	//exit();
	$min=$dbh->query("SELECT min(x) as mx,min(y) as my FROM `t_map`")->fetch();
	$dbh->exec("update t_map set x=x-$min[mx]+1,y=y-$min[my]+1");
	$dbh->exec("DELETE FROM `t_garageinfo` WHERE id  NOT  IN  ( SELECT `type_id` FROM `t_map` where type=3);");
}


init();
create();
echo '</div>';

//require_once 'left.php';
?>
<div id="Div2"> 


<div class="modal" id="bjcrkdhk" data-backdrop="static" >
<div class="modal-dialog "  style="display: inline-block; width: 350px;margin-left:30%;margin-top:50px;">
	<div class="modal-content">
		<div class="modal-header">
			<button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">×</span><span class="sr-only">Close</span></button>
			<h4 class="modal-title">编辑出入口信息</h4>
		</div>
		<div class="modal-body" style="height:120px;">
				<div style="">
					<label>编号</label>
					<input type="text" class="form-control" id="crkbh" placeholder=""><br>
					<label>名称</label>
					<input type="text" class="form-control" id="crkbz" placeholder="">
				</div>
		</div>
		<div class="modal-footer">
			<center>
				<button type="button" class="btn btn-success" data-dismiss="modal" onclick="setcrk()">保存</button>　
				<button type="button" class="btn btn-default" data-dismiss="modal">放弃修改</button>　
			</center>
		</div>
	</div>
</div>
</div>


<div class="modal" id="bjmkdhk" data-backdrop="static" style="margin:5% 10% 5% 10%;overflow-x:hidden;overflow-y:hidden">
<div class="modal-dialog "  style="display: inline;" >
	<div class="modal-content">
		<div class="modal-header">
			<button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">×</span><span class="sr-only">Close</span></button>
			<h4 class="modal-title">编辑模块信息</h4>
		</div>
		<div class="modal-body" style="height:auto;max-height:768px;min-height:360px;">
			<div class="col-sm-5 ">
				<div class="" style="margin-right:0px;display:inline">
					<label>模块编号</label>
					<input type="text" class="form-control" id="compotr" placeholder=""><br>
					<label>模块名称</label>
					<input type="text" class="form-control" id="mkname" placeholder=""><br>
					<label>模块层数</label>
					<input type="text" class="form-control" id="rows" placeholder="最大8层"><br>
					<label>模块列数</label>
					<input type="text" class="form-control" id="cols" placeholder="最大13列"><br>
					<label>横向速度</label>
					<input type="text" class="form-control" id="speedrows" placeholder=""><br>
					<label>纵向速度</label>
					<input type="text" class="form-control" id="speedcols" placeholder=""><br>
					<label>入口编号</label>
					<textarea type="text" class="form-control" id="instr" placeholder="入口编号"></textarea>
					<center>
					<button type="button" class="btn btn-success" style="margin-top:20px;" data-dismiss="modal" onclick="dosave()">保存模块信息</button>&nbsp;&nbsp;
					<button type="button" class="btn btn-default" style="margin-top:20px;" data-dismiss="modal">放弃修改</button>　
					</center>	
				</div>
			</div>
			<div class="col-sm-7 ">
				<div id="modulestate" style="font-size:28px;letter-spacing:1px;">
				</div>
				
			</div>
		</div>
	</div>
</div>
</div>

<form method="post" id="fmapedit">
&nbsp;X=<input style="width:20px;border:0;" name="x" id="x" value=0 readonly />,Y=<input style="width:20px;border:0;" name="y" id="y" value=0  readonly />
<br>
<select style="overflow-y:hidden;width:100px;" class="selectpicker" size="5" name="type" id="type" class="form-control">
<option value="1">入口</option>
<option value="2">出口</option>
<option value="4">道路</option>
<option value="0">墙壁</option>
<option value="3">车库模块</option>
</select>
<!--
<span class="round" id="suggest-align">
-->
        <input name="value"  type="hidden" class="input_key " id="value" placeholder="值"><br>
		<!--
        <span title="编辑模块" class="delquery" id="bjmk" style="display: none;"  ><span class="glyphicon glyphicon-edit"></span></span>
</span>
-->
<input type="hidden" name="do" value="yes">
</form>
<div style="text-align:center;margin-top:6px;">
<a class="btn btn-sm btn-primary" href="#" onclick="dosubmit()" ><span id="execcmd">编辑</span></a>
<a class="btn btn-sm btn-success" href="#" onclick="location.reload()">刷新</a><br>
<a class="btn btn-sm btn-danger" href="#" style="margin-top:4px;width:96%;" onclick="wipe()">清空地图</a>


<script>
var xx = document.getElementById("x");
var yy = document.getElementById("y");
<?php
	$zb=$dbh->query("select x,y,type from t_map ")->fetchAll();
	echo "var info=(".json_encode($zb).");\n";
?>
$('#rows').keyup(function () {
	if($('#rows').val()!=""){
		if($('#rows').val()>8)alert('最大8层！');
		if($('#rows').val()<1)alert('最少1层！');
	}
}); 
$('#cols').keyup(function () {
	if($('#cols').val()!=""){
		if($('#cols').val()>13)alert('最大13列！');
		if($('#cols').val()<1)alert('最少1列！');
	}
}); 
function wipe(){
	if(confirm("确认要清空地图？")){
		alert("Success! ");
		location.href='?do=wipemap';
	}
}	
for (var i=0; i<info.length; i++){
	if(info[i].type==4){
		eval('var td = document.getElementById("'+info[i].x+'_'+info[i].y+'")');
		var sum=0;
		for (var j=0; j<info.length; j++){
			if(info[j].x==info[i].x-1&&info[j].y==info[i].y)sum+=1;
			if(info[j].x==parseInt(info[i].x)+1&&info[j].y==info[i].y)sum+=4;
			if(info[j].y==info[i].y-1&info[j].x==info[i].x)sum+=8;
			if(info[j].y==parseInt(info[i].y)+1&info[j].x==info[i].x)sum+=2;
		}
		// if(sum==1||sum==4)sum=5;
		// if(sum==2||sum==8)sum=10;
		// if(sum==0)sum=15;
		td.style.background="url(img/road_"+sum+".png)repeat";
		//break;
		//alert(td.value);
	}
}
function dosubmit(){
	if((xx.value==0&&yy.value==0)||xx.value==''||yy.value=='')
	{
		alert('坐标错误');
		return false;
	}
	switch(type.value){
	case '1':case '2':dplcrkbj(type.value);//
		break;
	case '3':dplmkbj();
		break;	
	default: document.getElementById("fmapedit").submit();
	}
}


$("#type").click(function(){ 
	switch(type.value){
		case '3':
		$("#bjmk").show();
		$('#execcmd').html('编辑');
			break;
		case '4':case '0':
			$('#execcmd').html('添加');
			break;
		default:$('#execcmd').html('编辑');
		}
});
var arr=new Array();
arr[0]=0;
function dplcrkbj(type){
	$.ajax({
		type:"GET",url:"mapedit.php",
		data:{do:"getcrkinfo",x:$('#x').val(),y:$('#y').val(),type:type},
		success:function(data){
		var x=JSON.parse(data); 
		//alert(data);
		$('#crkbh').val(x.type_id);
		$('#crkbz').val(x.value);
		
	}});
	$("#bjcrkdhk").modal("toggle");
	
}

function setcrk(){
	$.ajax({
		type:"GET",url:"mapedit.php",
		data:{do:"setcrkinfo",x:$('#x').val(),y:$('#y').val(),type:$("#type").val(),type_id:$('#crkbh').val(),value:$('#crkbz').val()},
		success:function(data){
		//var x=JSON.parse(data); 
		alert(data);
		location.reload();
		
	}});
	//$("#bjcrkdhk").modal("toggle");
	
}

function dplmkbj(){ 
	$.ajax({
		type:"GET",url:"mapedit.php",
		data:{do:"getmkinfo",mkid:$('#value').val()},
		success:function(data){
		var x=JSON.parse(data); 
		var cars=x.map_queue.replace(/(^\s*)|(\s*$)/g, "").split(' ');
		var t="";
		
		var free=0;
		var instr="";
		for(var i=0;i<x.rows*x.cols;i++){
			arr[i+1]=0;
		}
		
		for(var i=0;i<x.rows*x.cols;i++){
			//String(cars[i]>>16)//状态
			//cars[i]&65535 编号
			if(cars[i]!='')arr[cars[i]&0x0000FFFF]=cars[i]>>16;
			if(cars[i]>>16==2)instr+=String(cars[i]&0x0000FFFF)+' ';
			if(cars[i]>>16==1)free++;
		}
		
		var ii=x.rows*x.cols;
		for(var i=0;i<x.rows;i++){
			for(var j=0;j<x.cols;j++){
				t+='<span class="glyphicon '+(arr[ii]==0?"glyphicon-ok-circle":(arr[ii]==1?"glyphicon-ban-circle":"glyphicon-log-in"))+'"></span>';
				ii--;
			}
			t+="<br>";
		}
		$('#modulestate').html(t);
		//alert(cars.length);
		
		$('#mkname').val(x.name);
		$('#rows').val(x.rows);
		$('#cols').val(x.cols);
		$('#speedrows').val(x.speedrows);
		$('#speedcols').val(x.speedcols);
		$('#instr').val(instr);    
		$('#compotr').val(x.id);    
	}});
	//$("#bjmkdhk").modal({backdrop:'static', keyboard: false});
	$("#bjmkdhk").modal("toggle"); 
}

function dosave(){ 
	//alert(1);
	var inarr=$('#instr').val().split(' ');
	for(var i=1;i<arr.length;i++){
		if(arr[i]==2)arr[i]=0;
		if(arr[i]<0||arr[i]>2)arr[i]=0;
	}
	for(var i=0;i<inarr.length;i++)	
		arr[inarr[i]]=2;
	var map_queue="";
	for(var i=1;i<arr.length;i++)
		map_queue+=String((arr[i]<<16)+i)+" ";
	$.ajax({
	type:"GET",url:"mapedit.php",
	data:{do:"setmkinfo",
	x:$('#x').val(),
	y:$('#y').val(),
	mkid:$('#mkname').val(),
	map_queue:map_queue,
	rows:$('#rows').val(),
	cols:$('#cols').val(),
	speedrows:$('#speedrows').val(),
	speedcols:$('#speedcols').val(),

	compotr:$('#compotr').val(),
	},
	cache:false,
	success:function(data){
		//var zt=JSON.parse(data);
		alert(data);
				location.reload();
	}});

	//alert(map_queue);
	//alert(arr);

}
function edit(x,y,t,v){
	var value = document.getElementById("value");
	var type = document.getElementById("type");	
	xx.value=x;
	yy.value=y;
	type.value=t;
	value.value=v;
	$("#bjmk").hide();
	switch(type.value){
		case '3':
		$("#bjmk").show();
		$('#execcmd').html('编辑');
			break;
		case '4':case '0':
			$('#execcmd').html('添加');
			break;
		default:$('#execcmd').html('编辑');
		}
	}
</script>
	
</div>
</div>
</div>
</body>
</html>
