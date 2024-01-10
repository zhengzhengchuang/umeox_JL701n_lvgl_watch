/*
  WebFont Demo javascript
  
  (C) 2013-2015 High-Logic B.V.
  
  http://www.high-logic.com
*/

var haveErrors = false;
var haveOTLF   = false;

function Initialize() {
  if (fctrial) {
    AddError("Because this Web Font is created with a trial version of FontCreator, only a subset of characters is available. See the FontCreator User Manual about the limitations of exported fonts during the trial period.");
  }
  if (symbolfont) {
    AddError("��������Ϊ�ɰ�� Windows ����. ���ǿ��ܲ�֧�������Ĳ���ϵͳ, ������������ƴд��鹦�ܻ᲻����. Unicode ��������з����ַ�, ��������Ƽ��㽫��������ת��Ϊ Unicode ����, ������������֧�־ɵ����. ת�� FontCreator �����˵�Ȼ��ѡ�񹤾� -> ת������ -> ת��Ϊ Unicode ����.");
  }
  BrowserCheck(otf.length > 0, colorfont);
  ProcessErrors();
  InitializeOpenTypeFeatures();
  UpdatePreviewText(document.getElementById("input"));
}

function AddError(aError) {
  haveErrors = true;
  id = document.getElementById('errorlist');
  id.innerHTML += "<li>" + aError + "</li>";
  return false;
}

function ProcessErrors() {
  if (!haveErrors) {
    document.getElementById('errors').style.display = "none";
  }
  else {
    document.getElementById("nojserror").style.display = "none";
  }
}

function DetermineBrowser() {
  var browserstr = navigator.userAgent.toLowerCase();
  var result = Array();
  result["name"] = "unknown";
  result["fullname"] = "unknown";
  result["version"] = "unknown";
  if (match = browserstr.match("chrome/([0-9]+)")) {
    result["name"] = "chrome";
    result["fullname"] = "Google Chrome";
    result["version"] = match[1];
  }
  else if (match = browserstr.match("firefox/([0-9]+)")) {
    result["name"] = "firefox";
    result["fullname"] = "Mozilla Firefox";
    result["version"] = match[1];
  }
  else if (match = browserstr.match("opera/([0-9]+)")) {
    result["name"] = "opera";
    result["fullname"] = "Opera";
    result["version"] = match[1];
  }    
  else if (match = browserstr.match("safari/([0-9]+)")) {
    result["name"] = "safari";
    result["fullname"] = "Apple Safari";
    result["version"] = match[1];
  }
  else if (match = browserstr.match("msie ([0-9]+)")) {
    result["name"] = "ie";
    result["fullname"] = "Microsoft Internet Explorer";
    result["version"] = match[1];
  }  
  else if (match = browserstr.match("trident/([0-9]+).+; .*? rv:([0-9]+)")) {
    /* IE 11 and up */
    if (match[1] >= 7) {
      result["name"] = "ie";
      result["fullname"] = "Microsoft Internet Explorer";
      result["version"] = match[2];
    }
  }   
  return result;
}

function DetermineOS() {
  var browserstr = navigator.userAgent.toLowerCase();
  var result = Array();
  result["name"] = "unknown";
  result["version"] = "unknown";
  if (match = browserstr.match("windows.*? ([0-9\.]+);")) {
    result["name"] = "windows";
	result["version"] = match[1];
  }
  return result;
}

function BrowserCheck(aOTLF, aColor) {
 
  var browser = DetermineBrowser();
  var os = DetermineOS();
  var id = document.getElementById("errorlist");

  switch (browser["name"]) {
    case "firefox" :
      if (aOTLF) {
	    if (browser["version"] < 4) {
          return AddError("����Ҫ���ٰ汾Ϊ FireFox 4 ����� CSS 3.0 �������, �ſ�ʹ�� OpenType Layout Features.");
        }
	  }
	  if (aColor) {
	    if (browser["version"] < 32) {
	      return AddError("����Ҫ���ٰ汾Ϊ Firefox 32 �������, ����ʹ�ò�ɫ����.");
      }
	  }
    break;
    case "chrome" : 
      if (browser["version"] < 22) {
        return AddError("����Ҫ���ٰ汾Ϊ Chrome 22 ����� CSS 3.0 �������, �ſ�ʹ�� OpenType Layout Features.");
      }
	  if (aColor) {
	    return AddError("Chrome �������֧�ֲ�ɫ����, �������汾��28.");
	  }
    break;
    case "ie" : 
      if (aOTLF && (browser["version"] < 10)) {
        return AddError("����Ҫ���ٰ汾Ϊ Internet Explorer 10 ����� CSS 3.0 �������, �ſ�ʹ�� OpenType Layout Features.");
      }
	  if (aColor) {
		if (browser["version"] < 11) {
	      return AddError("����Ҫ���ٰ汾Ϊ Internet Explorer 11 �������, �ſ�ʹ�ò�ɫ����.");
		}
		else {
		  if (os["version"] < 6.3) {
		    return AddError("����Ҫ���ٰ汾Ϊ Windows 8.1 �� Internet Explorer ����ʹ�ò�ɫ����. ��Ҳ������32λȫƽ̨ϵͳ��ʹ�� Firefox ��֧�ֲ�ɫ����, ���߿�ѡ��һ.");
		  }
		}
	  }
    break;
    case "opera" : 
      if (browser["version"] < 15) {
        return AddError("����Ҫ���ٰ汾Ϊ Opera 15 ����� CSS 3.0 �������, �ſ�ʹ�� OpenType Layout Features.");
      }
      else {
        return AddWarning("����: �˰汾�� Opera ��������ܲ�֧�� OpenType Layout Features.");
      }
	  if (aColor) {
	    return AddError("Opera �������֧�ֲ�ɫ����, �������汾��16.");
	  }
    break;
    default :
      return AddError("�޷��������������/��汾. OpenType Layout Features ��������ȷ����ʾ.");
    break;
  }
}

function UpdateFeatures() {
  var featurestring = "";

  altval = document.getElementById("alternate").value;
  
  for (i = 0; i < otf.length; i++) {
    id = document.getElementById("otf_" + otf[i][0]);
    if (i > 0) {
      featurestring += ",";
    }
//    featurestring += "'" + otf[i][0] + "' " + (id.checked ? "1" : "0");
    featurestring += "'" + otf[i][0] + "' " + (id.checked ? altval : "0");
  }  
  id = document.getElementById("preview");
  // Firefox 4+
  id.style.MozFontFeatureSettings = featurestring;
  // Chrome 20+ / Safari (OSX only)
  id.style.webkitFontFeatureSettings = featurestring;
  // Official CSS 3.0
  id.style.fontFeatureSettings = featurestring;
}

function SetAllFeatures(aValue) {
  for (i = 0; i < otf.length; i++) {
    id = document.getElementById("otf_" + otf[i][0]);
    id.checked = aValue;
  }  
  UpdateFeatures();
}

function SetDefaultFeatures() {
  for (i = 0; i < otf.length; i++) {
    id = document.getElementById("otf_" + otf[i][0]);
    id.checked = otf[i][2];
  }  
  UpdateFeatures();
}

function InitializeOpenTypeFeatures() {
  id = document.getElementById("otfeatures");
  if (otf.length == 0) {
    id.innerHTML += "�����岻�����κε� OpenType Layout Features ����.";
    return;
  
  }
  id.innerHTML += "<input type='button' value='����������' onclick='SetAllFeatures(false)'/> ";
  id.innerHTML += "<input type='button' value='��������' onclick='SetAllFeatures(true)'/> ";
  id.innerHTML += "<input type='button' value='Ĭ��' onclick='SetDefaultFeatures()'/><hr/>";
  for (i = 0; i < otf.length; i++) {
    checked = otf[i][2] ? " checked='checked'" : "";
    id.innerHTML += "<label><input id='otf_"+otf[i][0]+"'"+checked+" type='checkbox' onclick='UpdateFeatures()'> " + otf[i][0] + " - " + otf[i][1] + "</label><br/>";
  }
  UpdateFeatures();
}

function UpdatePreviewText(sender) {
  id = document.getElementById("preview");
  id.innerHTML = sender.value.replace(/\n/g, "<br/>");
}

function UpdatePreviewQuickPick(sender) {
  id = document.getElementById("input");
  switch (sender.value) {
    case "0" : 
      id.value = id.defaultValue;
    break;
    case "1" : 
      id.value = "abcdefghijklmnopqrstuvwxyz\r\nABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n1234567890";
    break;
    case "2" : 
      id.value = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed molestie augue vel quam dapibus sollicitudin. Sed vestibulum erat ac nibh varius vestibulum. Quisque a quam at est sodales pulvinar ac vel nisl. Cras sit amet consectetur dolor. Aliquam nisl lorem, iaculis eget aliquam pharetra, tincidunt id turpis. Ut sit amet nisl sed ipsum tempor luctus. Aenean vitae tristique sem. Pellentesque turpis dolor, lacinia id fermentum et, dapibus ac ipsum. Etiam nisi quam, feugiat vitae eleifend vel, luctus et mi.";
    break;
  }
  UpdatePreviewText(document.getElementById("input"));
}

function UpdateFontSize(sender) {
  id = document.getElementById("preview");
  id.style.fontSize = sender.value + "pt";
  id.style.lineHeight = sender.value + "pt";
}

function UpdateFontColorBG(sender) {
  id = document.getElementById("preview");
  id.style.background = "#" + sender.value;
}

function UpdateFontColorFG(sender) {
  id = document.getElementById("preview");
  id.style.color = "#" + sender.value;
}

function UpdateAlternate(sender) {
  UpdateFeatures();
}

function UpdateDirection(sender) {
  id = document.getElementById("preview");
  id.style.direction = sender.value;
}