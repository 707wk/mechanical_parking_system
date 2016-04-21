<?php 
/*************************************
 *CREATED :2016/4/19
 *TEXT    :立体车库管理后台顶部框架
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

</script>
<style>
a{
	cursor:default;
}

</style>
</head>
<body>

<nav class="navbar navbar-default">
        <div class="container-fluid" style="background-color:rgb(81,146,187);color:#fff;">
          <div class="navbar-header">
            <a class="navbar-brand" style="color:#fff;" href="#"><span class="glyphicon glyphicon-th-list">立体车库管理后台</span></a>
          </div>
          <div id="navbar" class="navbar-collapse collapse">
            <ul class="nav navbar-nav navbar-right" id="logandreg">
              <li><a onclick="window.parent.parent.document.getElementById('mainFrame').src='mapedit.php'" style="color:#fff;"><span class="glyphicon glyphicon-off"></span>&nbsp;安全退出</a></li>
            </ul>
          </div>
        </div>
      </nav>
</body>
</html>