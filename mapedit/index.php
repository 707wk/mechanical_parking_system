<!DOCTYPE HTML>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
<title>MapEdit</title>
<style>
//table,table td,table th{border:1px solid #fff;border-collapse:collapse;}
td{
	height:24px;
	width:24px;
	border:none;
	font-size:10px;
	color:#fff;
	text-align:center;
}
table{
	background-color:#000;
}
.wall {
	background:url(wall.png)repeat;
	//background-color:#690;
}
.road{
	background-color:#BDBBB3;
}
.in{
	background:url(in.png)repeat;
	//background-color:#3E8ECA;
}
.out{
	background:url(out.png)repeat;
	//background-color:#f60;	
}
.module{
	background:url(module.png)repeat;
	//background-color:#339;	
}
#Div0
{
  float:left; width:auto; 
}
#Div1 
{
  float:left; width:auto; 
}
#Div2 
{
  margin-left:20px;
  width:300px;float:right;
}
</style>
</head>
<body>
<div id="Div0">
<h3>Map Editor</h3>
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

	for($i=0;$i<=$maxx+1;$i++){
		echo '<table border="0" cellpadding="0" cellspacing="0">';
		for($j=0;$j<=$maxy+1;$j++){
			$class="wall";$value="";$t="0";
			if(!empty($map[$i][$j])){
				$class=$map[$i][$j]['type'];
				$value=$map[$i][$j]['value'];
				$t=$map[$i][$j]['t'];
			}
			echo "<td class=\"{$class}\" onclick=\"edit({$i},{$j},{$t},'{$value}');\" onmousedown=\"this.style.opacity='0.5';\" onmousemove=\"this.style.opacity='1';\" onmouseup=\"this.style.opacity='1';\">{$value}</td>";	
		}
		echo "</tr>";
	}
	echo "</table>";

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
create();

?>
</div>
<div id="Div2">

<form method="post" onsubmit="check();">
Coordinate:(<input style="width:20px;" name="x" id="x"/>,<input style="width:20px;" name="y" id="y"/>)
<br>
Type:&nbsp;<select name="type" id="type">
<option value="1">in</option>
<option value="2">out</option>
<option value="3">module</option>
<option value="4">road</option>
<option value="0">wall</option>

</select>
<br>
Value:<input name="value" id="value" ><br>
<input type="hidden" name="do" value="yes"><br>
<input type="submit" value="Save"><br><br>
</form><button onclick="location='?'">Refresh</button>
</div>
</div>
<script>
var xx = document.getElementById("x");
var yy = document.getElementById("y");
function check(){
	if(xx.value==0||yy.value==0)
	{
		alert('最外层是墙，不可操作！');
		return false;
	}
	return true;
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
	
	
	
	
	
