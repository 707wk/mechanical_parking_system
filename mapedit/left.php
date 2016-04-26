<?php 
/*************************************
 *CREATED :2016/4/20
 *TEXT    :立体车库左边框架
 *EMAIL   :dksx@qq.com
 *************************************/
 require_once "main.php";
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
}
a{
	cursor:default;
	color:#fff;
}
</style>
</head>
<body>
	<div class="span2" style="height:0px;">
		<ul  class="nav nav-list" style="text-align:center">
			<li class=""><a onclick="go('state.php')" ><span class="glyphicon glyphicon-info-sign"></span>&nbsp;模块状态</a></li>
			<li class=""><a onclick="go('mapedit.php')" ><span class="glyphicon glyphicon-edit"></span>&nbsp;地图设置</a></li>
			<li class=""><a onclick="go('usermgr.php')" ><span class="glyphicon glyphicon-user"></span>&nbsp;用户管理</a></li>
			<li class=""><a onclick="go('peicemgr.php')" ><span class="glyphicon glyphicon-usd"></span>&nbsp;收费管理</a></li>
       </ul>
     </div>
</body>
</html>