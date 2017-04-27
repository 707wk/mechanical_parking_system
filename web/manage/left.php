<?php 
/*************************************
 *CREATED :2016/4/20
 *TEXT    :立体车库左边框架
 *EMAIL   :dksx@qq.com
 *************************************/
 require_once "main.php";
  needLogin();
?>
<!DOCTYPE html >
<html >
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>立体车库管理后台</title>
<link href="libs/css/bootstrap.min.css" rel="stylesheet">
<script src="libs/js/jquery.min.js"></script>
<script src="libs/js/bootstrap.min.js"></script>
<script>
function go(uri){
//	$('mainFrame').attr("src",uri);
	window.parent.parent.document.getElementById("mainFrame").src = uri; 
}
</script>

<style>
body{
	background-color:rgb(49,64,93);
	-webkit-touch-callout: none;  
	-webkit-user-select: none;  
	-khtml-user-select: none;  
	-moz-user-select: none;  
	-ms-user-select: none;  
	user-select: none;  
}
a{
	cursor:default;
	color:#fff;
}
a{
	cursor:pointer;
}
</style>
</head>

<body>
<script>
document.oncontextmenu=function(e){return false;}  
</script>
	<div class="span2" style="height:0px;">
		<ul  class="nav nav-list" style="text-align:center">
			<li class=""><a onclick="go('state.php')" ><span class="glyphicon glyphicon-info-sign"></span>&nbsp;模块状态</a></li>
			<li class=""><a onclick="go('carstate.php')" ><span class="glyphicon glyphicon-tasks"></span>&nbsp;车辆状态</a></li>
			<li class=""><a onclick="go('mapedit.php')" ><span class="glyphicon glyphicon-edit"></span>&nbsp;地图设置</a></li>
			<li class=""><a onclick="go('usermgr.php')" ><span class="glyphicon glyphicon-user"></span>&nbsp;用户管理</a></li>
			<li class=""><a onclick="go('permgr.php')" ><span class="glyphicon glyphicon-asterisk"></span>&nbsp;权限管理</a></li>
			<li class=""><a onclick="go('peicemgr.php')" ><span class="glyphicon glyphicon-usd"></span>&nbsp;收费管理</a></li>
			<li class=""><a onclick="go('history.php')" ><span class="glyphicon glyphicon-calendar"></span>&nbsp;历史记录</a></li>
       </ul>
     </div>
</body>
</html>