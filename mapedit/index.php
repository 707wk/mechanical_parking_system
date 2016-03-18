<?php
/*************************************
 *CREATED :2016/3/14
 *TEXT    :停车场地图管理系统
 *EMAIL   :dksx@qq.com
 *************************************/
$dbh=null;
try
{
	$dbh = new PDO("mysql:host=localhost;dbname=oldcar","oldcar","BbNMZrmAAdCWhmjz",
	array(PDO::ATTR_PERSISTENT => true)); 
    $dbh->query("set names utf8");
}
catch (PDOException $e)
{
	echo 'Connection failed: ' . $e->getMessage();
	die;
}

switch(@$_GET['do']){
	case "wipemap":
	$dbh->exec('delete from map where 1');
	header("Location:index.php");
	exit();
	case 'getmkinfo':
		if($dbh->query("select * from t_garageinfo where name=$_GET[mkid]")->rowCount()==0){
			$dbh->exec("INSERT INTO `t_garageinfo` (`name`, `rows`, `cols`, `speedrows`, `speedcols`,  `map_queue`, `compotr`) VALUES
('$_GET[mkid]', 5, 4, 2.000, 1.100, '131073 2 65539 4 65541 65542 65543 8 65545 65546 65547 12 65549 65550 15 16 65553 18 19 20 ', 3);");
		}
		$result=$dbh->query("select * from t_garageinfo where name=$_GET[mkid]")->fetch();
		echo json_encode($result);
		exit();
	case 'setmkinfo':
		//mkname  map_queue rows cols speedrows speedcols state
		$dbh->exec("update t_garageinfo set  map_queue='$_GET[map_queue]', rows='$_GET[rows]', cols='$_GET[cols]', speedrows='$_GET[speedrows]', speedcols='$_GET[speedcols]',compotr='$_GET[compotr]' where name=$_GET[mkid]");
		exit('更新成功！');
		
}

if(isset($_POST['do'])&&$_POST['y']!=""&&$_POST['x']!=""):
	$x=$_POST['x'];
	$y=$_POST['y'];
	$value=$_POST['value'];
	$type=$_POST['type'];
	if($dbh->query("select id from map where x=$x and y=$y")->fetch()){
		$dbh->exec("update map set type=$type,value='$value' where x=$x and y=$y");
	}
	else {
		$dbh->exec("INSERT INTO `map`(`x`, `y`, `type`, `value`) VALUES ($x,$y,$type,'$value')");
	}
	if($type==0)$dbh->exec("DELETE FROM `map` WHERE type=0");
		header("Location:index.php");
	exit();
endif;

?>
<!DOCTYPE HTML>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
<link href="http://libs.baidu.com/bootstrap/3.0.3/css/bootstrap.min.css" rel="stylesheet">
<script src="//cdn.bootcss.com/jquery/1.11.3/jquery.min.js"></script>
<script src="http://libs.baidu.com/bootstrap/3.0.3/js/bootstrap.min.js"></script>
<title>停车场地图管理系统</title>
<style>
body {
	font-family: '微软雅黑';
	background-color: #f5f5f5;
}
input {
	background-color: #f5f5f5;
}
td{
	height:22px;
	width:22px;
	border:none;
	font-size:13px;
	color:#fff;
	text-align:center;
	border-radius:1px;
	
}
table{
	background-color:#000;
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
</style>
</head>
<body>

<div id="Div0">

<h3>停车场地图管理系统</h3>

<div id="Div1">
<?php 

function create(){
	global $dbh;
	$arr=$dbh->query("select * from map ")->fetchAll();
	//var_dump($arr);
	$maxx=$maxy=0;
	$map;
	foreach($arr as $a){
		$type=$a['type'];
		$type=array(0=>'wall','mk_in','out','module','road');
		$map[$a['x']][$a['y']]=array('t'=>$a['type'],'type'=>$type[$a['type']],'value'=>$a['value']);		
		if($a['x']>$maxx)$maxx=$a['x'];
		if($a['y']>$maxy)$maxy=$a['y'];
	}
	echo '<table border="0" cellpadding="0" cellspacing="0">'."\n";
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
	echo "</table>";

}

function init(){
	global $dbh;
	//var_dump( );
	//exit();
	$min=$dbh->query("SELECT min(x) as mx,min(y) as my FROM `map`")->fetch();
	$dbh->exec("update map set x=x-$min[mx]+1,y=y-$min[my]+1");
}


init();
create();
echo '</div>';

//require_once 'left.php';
?>
<div id="Div2"> 
<div class="modal" id="bjmkdhk" >
<div class="modal-dialog "  style="display: inline-block; width: 450px;;margin-left:30%;margin-top:50px;">
	<div class="modal-content">
		<div class="modal-header">
			<button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">×</span><span class="sr-only">Close</span></button>
			<h4 class="modal-title">编辑模块信息</h4>
		</div>
		<div class="modal-body" style="height:320px;">
			<div class="col-sm-7 ">
				<div class="form-group" style="">
					<label class="col-sm-6 control-label">模块名称</label>
					<div class="col-sm-6">
					<input type="text" class="form-control" id="mkname" placeholder="">
					</div>
					<label class="col-sm-6 control-label">编号号码</label>
					<div class="col-sm-6">
					<input type="text" class="form-control" id="compotr" placeholder="">
					</div>
					<label class="col-sm-6 control-label">模块层数</label>
					<div class="col-sm-6">
					<input type="text" class="form-control" id="rows" placeholder="">
					</div> 
					<label class="col-sm-6 control-label">模块列数</label>
					<div class="col-sm-6">
					<input type="text" class="form-control" id="cols" placeholder="">
					</div>
					<label class="col-sm-6 control-label">横向速度</label>
					<div class="col-sm-6">
					<input type="text" class="form-control" id="speedrows" placeholder="">
					</div>
					<label class="col-sm-6 control-label">纵向速度</label>
					<div class="col-sm-6">
					<input type="text" class="form-control" id="speedcols" placeholder="">
					</div>
					<label class="col-sm-6 control-label">入口编号</label>
					<div class="col-sm-6">
					<textarea type="text" class="form-control" id="instr" placeholder="入口编号"></textarea>
					</div>
				</div>
			</div>
			<div class="col-sm-5 ">
				<div id="modulestate" style="font-size:32px;letter-spacing:1px;">
				</div>
				
			</div>
		</div>
		<div class="modal-footer">
			<center>
				<button type="button" class="btn btn-success" data-dismiss="modal" onclick="dosave()">保存模块信息</button>　
				<button type="button" class="btn btn-default" data-dismiss="modal">放弃修改</button>　
			</center>
		</div>
	</div>
</div>
</div>

<form method="post" id="fmapedit">
&nbsp;X=<input style="width:20px;border:0;" name="x" id="x" value=0 readonly />,Y=<input style="width:20px;border:0;" name="y" id="y" value=0  readonly />
<br>
<select style="overflow-y:hidden;width:100px;" class="selectpicker" size="5" name="type" id="type" class="form-control">
<option value="1">车库入口</option>
<option value="2">车库出口</option>
<option value="3">车库模块</option>
<option value="4">道路</option>
<option value="0">墙壁</option>
</select>
<br>
<span class="round" id="suggest-align">
        <input name="value" class="input_key " id="value" placeholder="值"><br>
        <span title="编辑模块" class="delquery" id="bjmk" style="display: none;"  ><span class="glyphicon glyphicon-edit"></span></span>
</span>

<input type="hidden" name="do" value="yes">
</form>
<div style="text-align:center;">
<a class="btn btn-sm btn-primary" href="#" onclick="dosubmit()">保存</a>
<a class="btn btn-sm btn-success" href="#" onclick="location='?'">刷新</a><br>
<a class="btn btn-sm btn-danger" href="#" style="margin-top:4px;width:96%;" onclick="wipe()">清空地图</a>


<script>
var xx = document.getElementById("x");
var yy = document.getElementById("y");
<?php
	$zb=$dbh->query("select x,y,type from map ")->fetchAll();
	echo "var info=(".json_encode($zb).");\n";
?>

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
		td.style.background="url(img/road_"+sum+".png)repeat";
		//break;
		//alert(td.value);
	}
}
function dosubmit(){
	if(xx.value==''||yy.value=='')
	{
		alert('坐标错误');
		return false;
	}
	//return true;
	document.getElementById("fmapedit").submit();	
}

$("#bjmk").hide();
$("#type").click(function(){ 
	if(type.value==3)$("#bjmk").show();
	else $("#bjmk").hide();
});
var arr=new Array();
arr[0]=0;
$("#bjmk").click(function(){ 
	$.ajax({
		type:"GET",url:"index.php",
		data:{do:"getmkinfo",mkid:$('#value').val()},
		success:function(data){
		var x=JSON.parse(data); 
		var cars=x.map_queue.replace(/(^\s*)|(\s*$)/g, "").split(' ');
		var t="";
		
		var free=0;
		var instr="";
		for(var i=0;i<cars.length;i++){
			//String(cars[i]>>16)//状态
			//cars[i]&65535 编号
			if(cars[i]!='')
			arr[cars[i]&0x0000FFFF]=cars[i]>>16;
			if(cars[i]>>16==2)instr+=String(cars[i]&0x0000FFFF)+' ';
			if(cars[i]>>16==1)free++;
		}
		
		var ii=cars.length;
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
		$('#compotr').val(x.compotr);    
	}});
	$("#bjmkdhk").modal("toggle");

});
function dosave(){ 
	//alert(1);
	var inarr=$('#instr').val().split(' ');
	for(var i=1;i<arr.length;i++)if(arr[i]==2)arr[i]=0;
	for(var i=0;i<inarr.length;i++)	
		arr[inarr[i]]=2;
	var map_queue="";
	for(var i=1;i<arr.length;i++)
		map_queue+=String((arr[i]<<16)+i)+" ";
	$.ajax({
	type:"GET",url:"index.php",
	data:{do:"setmkinfo",
	mkid:$('#mkname').val(),
	mkname:$('#mkname').val(),
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
	if(type.value==3)$("#bjmk").show();
	else $("#bjmk").hide();
}
</script>
	
</div>
</div>
</div>
</body>
</html>
