<!DOCTYPE html >
<html >
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>立体车库管理后台</title>
<link rel="stylesheet" href="css/index.css" type="text/css" media="screen" />
<link href="http://libs.baidu.com/bootstrap/3.0.3/css/bootstrap.min.css" rel="stylesheet">
<script src="//apps.bdimg.com/libs/jquery/1.11.3/jquery.js"></script>
<script src="http://libs.baidu.com/bootstrap/3.0.3/js/bootstrap.min.js"></script>
<script>
function go(uri){
	$('#myframe').attr("src",uri);
}
</script>
<style>

</style>

</head>
<body>

<div class="container-fluid"  style="">
  <div class="row"style="padding-bottom:100%" >
    <div class="col-xs-2" style="cursor:default;">
	<div class="span2" style="height:0px;">
		<ul  class="nav nav-list" style="text-align:center">
			<li class=""><a onclick="go('state.php')" ><span class="glyphicon glyphicon-tasks"></span>模块状态</a></li>
			<li class=""><a onclick="go('mapedit.php')" ><span class="glyphicon glyphicon-tasks"></span>地图设置</a></li>
			<li class=""><a onclick="go('usermgr.php')" ><span class="glyphicon glyphicon-tasks"></span>用户管理</a></li>
			<li class=""><a onclick="go('pricemgr.php')" ><span class="glyphicon glyphicon-tasks"></span>收费管理</a></li>
       </ul>
     </div>
	</div>
	
    <div class="col-xs-10" >
        <iframe id="myframe"  src="state.php" scrolling="auto" style="overflow:visible;width:100%;heught:100%;" frameborder="no" width="100%" height="900px;"></iframe>
	</div>
</div>
</div>

   

</body>
</html>