(function($, owner) {
	
	owner.setToken = function(setting) {
		localStorage.setItem('$token', setting);
	}
	owner.getToken = function() {
		return localStorage.getItem('$token');
	}
	owner.setsrvip = function(setting) {
		localStorage.setItem('$srvip', setting);
	}
	owner.getsrvip = function() {
		var dip='http://carserver.ngrok.cc/';
		var ip= localStorage.getItem('$srvip');
		if(ip==''||ip==null){
			app.setsrvip(dip);
			return dip;
		}
		return ip; 
	}
	owner.setSettings = function(settings) {
		settings = settings || {};
		localStorage.setItem('$settings', JSON.stringify(settings));
	}
	owner.getSettings = function() {
		var settingsText = localStorage.getItem('$settings') || "{}";
		return JSON.parse(settingsText);
	}
	
}(mui, window.app = {}));
(function($) {
	$.enterfocus = function(selector, callback) {
		var boxArray = [].slice.call(document.querySelectorAll(selector));
		for (var index in boxArray) {
			var box = boxArray[index];
			box.addEventListener('keyup', function(event) {
				if (event.keyCode == 13) {
					var boxIndex = boxArray.indexOf(this);
					if (boxIndex == boxArray.length - 1) {
						if (callback) callback();
					} else {
						//console.log(boxIndex);
						var nextBox = boxArray[++boxIndex];
						nextBox.focus();
					}
				}
			}, false);
		}
	};
}(window.mui = window.mui || {}));