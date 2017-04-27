<?php 
/*************************************
 *CREATED :2016/4/19
 *TEXT    :立体车库管理后台顶部框架
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

</script>
<style>
body{
	-webkit-touch-callout: none;  
	-webkit-user-select: none;  
	-khtml-user-select: none;  
	-moz-user-select: none;  
	-ms-user-select: none;  
	user-select: none;  
}
a{
	cursor:default;
}

</style>
</head>
<body>
<script>
document.oncontextmenu=function(e){return false;}  
</script>
<nav class="navbar navbar-default">
        <div class="container-fluid" style="background-color:rgb(81,146,187);color:#fff;">
          <div class="navbar-header">
            <a class="navbar-brand" style="color:#fff;" href="#"><span class="glyphicon glyphicon-th-list">立体车库管理后台</span></a>
          </div>
          <div id="navbar" class="navbar-collapse collapse">
            <ul class="nav navbar-nav navbar-right" id="logandreg">
              <li><a onclick="window.top.location.href='login.php?logout=true'" style="color:#fff;cursor:pointer;"><span class="glyphicon glyphicon-off"></span>&nbsp;安全退出</a></li>
            </ul>
          </div>
        </div>
      </nav>
</body>
</html>