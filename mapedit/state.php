<!DOCTYPE html >
<html >
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>state</title>
<link rel="stylesheet" href="css/index.css" type="text/css" media="screen" />
<link href="http://libs.baidu.com/bootstrap/3.0.3/css/bootstrap.min.css" rel="stylesheet">
<script src="//apps.bdimg.com/libs/jquery/1.11.3/jquery.js"></script>
<script src="http://libs.baidu.com/bootstrap/3.0.3/js/bootstrap.min.js"></script>
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
			t="<table border=1><tr>";
			var xx=JSON.parse(data); 
			$.each(xx, function(i, x){      
				t+="<td>";
				t+=gethtml(x);
				t+="模块"+x.id+"</td>";
				i++;
				if(i<5&&i%5==0)t+="</tr><tr>"
	　　}); 
		t+="</tr></table>";
			$('#state').html(t);
	}});
	// return t;
}
		
setpage();
</script>
<style>

</style>

</head>
<body>
<div id="state" style="font-size:20px;">
</div>
</body>
</html>