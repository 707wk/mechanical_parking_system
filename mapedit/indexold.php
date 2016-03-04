<!DOCTYPE HTML>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
<title>MapEdit</title>
<style>
body {font-family: '微软雅黑';}
td{
	height:22px;
	width:22px;
	border:none;
	font-size:10px;
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
.in{
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
  width:190px;
}
#Div1 
{
  margin-left:20px;
  
  float:right;
}
.button {
	display: inline-block;
	zoom: 1; /* zoom and *display = ie7 hack for display:inline-block */
	*display: inline;
	vertical-align: baseline;
	margin: 0 2px;
	outline: none;
	cursor: pointer;
	text-align: center;
	text-decoration: none;
	font: 14px/100% Arial, Helvetica, sans-serif;
	padding: .5em 2em .55em;
	text-shadow: 0 1px 1px rgba(0,0,0,.3);
	-webkit-border-radius: .5em; 
	-moz-border-radius: .5em;
	border-radius: .5em;
	-webkit-box-shadow: 0 1px 2px rgba(0,0,0,.2);
	-moz-box-shadow: 0 1px 2px rgba(0,0,0,.2);
	box-shadow: 0 1px 2px rgba(0,0,0,.2);
}
.button:hover {
	text-decoration: none;
}
.button:active {
	position: relative;
	top: 1px;
}
.hg {margin:5px;width:80%;}

.bigrounded {
	-webkit-border-radius: 2em;
	-moz-border-radius: 2em;
	border-radius: 2em;
}
.medium {
	font-size: 12px;
	padding: .4em 1.5em .42em;
}
.small {
	font-size: 11px;
	padding: .2em 1em .275em;
}
.blue {
	color: #d9eef7;
	border: solid 1px #0076a3;
	background: #0095cd;
	background: -webkit-gradient(linear, left top, left bottom, from(#00adee), to(#0078a5));
	background: -moz-linear-gradient(top,  #00adee,  #0078a5);
	filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#00adee', endColorstr='#0078a5');
}
.blue:hover {
	background: #007ead;
	background: -webkit-gradient(linear, left top, left bottom, from(#0095cc), to(#00678e));
	background: -moz-linear-gradient(top,  #0095cc,  #00678e);
	filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#0095cc', endColorstr='#00678e');
}
.blue:active {
	color: #80bed6;
	background: -webkit-gradient(linear, left top, left bottom, from(#0078a5), to(#00adee));
	background: -moz-linear-gradient(top,  #0078a5,  #00adee);
	filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#0078a5', endColorstr='#00adee');
}
.orange {
	color: #fef4e9;
	border: solid 1px #da7c0c;
	background: #f78d1d;
	background: -webkit-gradient(linear, left top, left bottom, from(#faa51a), to(#f47a20));
	background: -moz-linear-gradient(top,  #faa51a,  #f47a20);
	filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#faa51a', endColorstr='#f47a20');
}
.orange:hover {
	background: #f47c20;
	background: -webkit-gradient(linear, left top, left bottom, from(#f88e11), to(#f06015));
	background: -moz-linear-gradient(top,  #f88e11,  #f06015);
	filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#f88e11', endColorstr='#f06015');
}
.orange:active {
	color: #fcd3a5;
	background: -webkit-gradient(linear, left top, left bottom, from(#f47a20), to(#faa51a));
	background: -moz-linear-gradient(top,  #f47a20,  #faa51a);
	filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#f47a20', endColorstr='#faa51a');
}

h2{
	text-align:center;
}

.valuetext {
	max-width:200px;
	resize: none;
    color:#333;
    line-height:normal;
    font-family:"Microsoft YaHei",Tahoma,Verdana,SimSun;
    font-style:normal;
    font-variant:normal;
    font-size-adjust:none;
    font-stretch:normal;
    font-weight:normal;
    margin-top:0px;
    margin-bottom:0px;
    margin-left:0px;
    padding-top:4px;
    padding-right:4px;
    padding-bottom:4px;
    padding-left:4px;
    font-size:15px;
    outline-width:medium;
    outline-style:none;
    outline-color:invert;
    border-top-left-radius:3px;
    border-top-right-radius:3px;
    border-bottom-left-radius:3px;
    border-bottom-right-radius:3px;
    text-shadow:0px 1px 2px #fff;
    background-attachment:scroll;
    background-repeat:repeat-x;
    background-position-x:left;
    background-position-y:top;
    background-size:auto;
    background-origin:padding-box;
    background-clip:border-box;
    background-color:rgb(255,255,255);
    margin-right:8px;
    border-top-color:#ccc;
    border-right-color:#ccc;
    border-bottom-color:#ccc;
    border-left-color:#ccc;
    border-top-width:1px;
    border-right-width:1px;
    border-bottom-width:1px;
    border-left-width:1px;
    border-top-style:solid;
    border-right-style:solid;
    border-bottom-style:solid;
    border-left-style:solid;
}

.valuetext:focus {
     border: 1px solid #fafafa;
    -webkit-box-shadow: 0px 0px 6px #007eff;
     -moz-box-shadow: 0px 0px 5px #007eff;
     box-shadow: 0px 0px 5px #007eff;   
    
}

</style>
</head>
<body bgcolor=#BDBBB3>
<div id="Div0">
<h2>MapEdit for Parking Management</h2>
<div id="Div1">
<?php 
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

function create(){
	global $dbh;
	$arr=$dbh->query("select * from map ")->fetchAll();
	//var_dump($arr);
	$maxx=$maxy=0;
	$map;
	foreach($arr as $a){
		$type=$a['type'];
		$type=array(0=>'wall','in','out','module','road');
		$map[$a['x']][$a['y']]=array('t'=>$a['type'],'type'=>$type[$a['type']],'value'=>$a['value']);		
		if($a['x']>$maxx)$maxx=$a['x'];
		if($a['y']>$maxy)$maxy=$a['y'];
	}
	echo '<table border="5" cellpadding="0" cellspacing="0">'."\n";
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
	
endif;

init();
create();

?>
</div>
<div id="Div2">
<hr>
<form method="post" id="fmapedit">
Coordinate(<input style="width:20px;" name="x" id="x"/>,<input style="width:20px;" name="y" id="y"/>)
<br>
Type:&nbsp;<select name="type" id="type">
<option value="1">in</option>
<option value="2">out</option>
<option value="3">module</option>
<option value="4">road</option>
<option value="0">wall</option>
</select>
<br>
Value:<br><textarea name="value" id="value" maxlength="50" class="valuetext"></textarea><br><br>
<input type="hidden" name="do" value="yes">
</form>
<a class="button orange" href="#" onclick="dosubmit()">Save</a>
<a class="button blue" href="#" onclick="location='?'">Ref</a>
<hr>
</div>
</div>
<script>
var xx = document.getElementById("x");
var yy = document.getElementById("y");
<?php
	$zb=$dbh->query("select x,y,type from map ")->fetchAll();
	echo "var info=(".json_encode($zb).");\n";
?>
	
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

function edit(x,y,t,v){
	var value = document.getElementById("value");
	var type = document.getElementById("type");	
	xx.value=x;
	yy.value=y;
	type.value=t;
	value.value=v;

}

</script>
</body>
</html>
	
	
	
	
	
