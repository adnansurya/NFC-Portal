function pilihJenis() {
     
    var e = document.getElementById("identitas");
    var jenisId = e.options[e.selectedIndex].value;
    if(jenisId == "home"){
        document.getElementById("overlay").style.display = "none";
    }else if(jenisId == "visitor"){
        document.getElementById("overlay").style.display = "block";
    }
    
  }
  
  function off() {
    document.getElementById("overlay").style.display = "none";
  }