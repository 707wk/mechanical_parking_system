<?php 
/*************************************
 *CREATED :2016/4/20
 *TEXT    :立体车库状态
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
<style>
.bk{
	border:5px solid #aaaaaa;
	border-radius: 5px;
	-moz-border-radius: 5px;
	-webkit-border-radius: 5px;
	padding:2px;
}
.bk2{
	padding-left:20px;
	margin-left:20px;
	border:1px solid #aaa;
	width:270px;
	background-color:#D6FFD6;
}
body{
	background-color: #F2F2F2;
}
.top{
	text-align:left;
	margin-left:20px;
}
.mk{
	font-size:14px;
	border-bottom:#000000 1px dashed;
	margin-bottom:3px;
}
</style>
<script>
function gethtml(x){
	var arr=new Array(),t="";
	arr[0]=0;
	var cars=x.map_queue.replace(/(^\s*)|(\s*$)/g, "").split(' ');
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
		return t;
}
function setpage(id){ 
	
	$.ajax({
		type:"GET",url:"mapedit.php",
		data:{do:"getallmkinfo"},
		// async: false,
		success:function(data){
			var i=0,t="";	
			t="<table border=0><tr>";
			var xx=JSON.parse(data); 
			$.each(xx, function(i, x){      
				t+="<td><div class='bk'><p class='mk'>模块"+x.id+"</p>";
				t+="";
				t+=gethtml(x);
				t+="</div></td><td>&nbsp;</td>";
				i++;
				if(i%5==0)t+="</tr><tr>"
	　　}); 
		t+="</tr></table>";
			$('#state').html(t);
	}});
	// return t;
}
		
setpage();
</script>

</head>
<body>
<h3 class="top">【模块状态】</h3>
<div class="bk2">
<table style="font-size:15px;margin-bottom:0px;">
	<tr>
	<td  ></td> <td>　</td>
		<td class=" " ><span class="glyphicon glyphicon-ok-circle"></span></td> <td>空闲　</td>
		<td class=" "><span class="glyphicon glyphicon-ban-circle"></span></td> <td>有车　</td>
		<td class=" "><span class="glyphicon glyphicon-log-in"></span></td> <td>出入口</td>
	</tr>
</table>
</div>
<div id="state" style="font-size:20px;margin-left:20px;">
</div>
</body>
</html>