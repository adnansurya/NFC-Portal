const functions = require('firebase-functions');

var admin = require('firebase-admin');
var path = require('path');
// var serviceAccount = require(path.join(__dirname, 'mksrobotics-firebase-adminsdk-ns7lo-cfe0562851.json'));
var serviceAccount = require(path.join(__dirname, "myclasswebsite-3eca2-firebase-adminsdk-taamm-792fe5168d.json"));

admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://myclasswebsite-3eca2.firebaseio.com"
});

const db = admin.database();

let newData;
let original;
let idLog;
exports.addTime = functions.database.ref('/Log/{pushId}')
    .onCreate((change, context) => {
      // Grab the current value of what was written to the Realtime Database.
      original = change.val()
      newData = JSON.stringify(original);
      idLog = context.params.pushId;
      console.log("NEW : " + newData);
      console.log('ID : ' + idLog);
      

      var currentDate = new Date();
  
      var date = currentDate.getDate();
      var month = currentDate.getMonth(); //Be careful! January is 0 not 1
      var year = currentDate.getFullYear();
      var hour = currentDate.getHours(); // GMT +0
      var minute = currentDate.getMinutes();
      var second = currentDate.getSeconds();
    
      let real_hour = hour + 8;
      if(real_hour >= 24){
        real_hour = real_hour - 24;
      }
    
      var dateString = date + "-" +(month + 1) + "-" + year + " " + (real_hour) + ":" + minute +  ":" + second;
    
      waktu =  dateString;
      console.log("WAKTU : "+ waktu);

      return db.ref('Log/'+idLog).update({
          Waktu : waktu
        });

});
