//<script type="module">
      // Import the functions you need from the SDKs you need
      import { initializeApp } from "https://www.gstatic.com/firebasejs/9.6.2/firebase-app.js";
      import { getDatabase, ref, set, get, child, update, remove,onValue, query, limitToLast} from "https://www.gstatic.com/firebasejs/9.6.2/firebase-database.js";
      // TODO: Add SDKs for Firebase products that you want to use
      // https://firebase.google.com/docs/web/setup#available-libraries
    
      // Your web app's Firebase configuration
      // For Firebase JS SDK v7.20.0 and later, measurementId is optional
      const firebaseConfig = {
        apiKey: "AIzaSyCL1c8gSblusSfFoePq0HHUkyCfzEcxdZE",
        authDomain: "cucumber-20a25.firebaseapp.com",
        databaseURL: "https://cucumber-20a25-default-rtdb.firebaseio.com",
        projectId: "cucumber-20a25",
        storageBucket: "cucumber-20a25.appspot.com",
        messagingSenderId: "770806817191",
        appId: "1:770806817191:web:befe69073d30af619a5682",
        measurementId: "G-82HKX8FLBQ"
      };
    
      // Initialize Firebase
      const app = initializeApp(firebaseConfig);
      const db = getDatabase();

      var temp = document.getElementById("temp1");
      var hum = document.getElementById("hum1");
      var nh3 = document.getElementById("nh31");
      var hmm = document.getElementById("thm");

      var selBtn = document.getElementById("Selbtn");

      /*function SelectData()
      {
        const dbref = ref(db);

        get(child(dbref,"test")).then((snapshot)=>{
          if(snapshot.exists()){
            temp.value = snapshot.val().bool;
            hum.value = snapshot.val().int;
          }
          else{
            alert("No data found");
          }
        })
        .catch((error)=>{
          alert("unsuccessful, error"+error);
        });
      }

      selBtn.addEventListener('click', SelectData);*/

      //const starCountRef = ref(db, "DHT/" + "post/");
      const starCountRef = ref(db, "test");
      onValue(starCountRef, (snapshot) => 
      {
        temp.value = snapshot.val().temp;
        hum.value = snapshot.val().hum;
        nh3.value = snapshot.val().timestamp;
      });
      const Conf1 = ref(db, "json");

      onValue(query(Conf1, limitToLast(100)), (snapshot) => 
      {
        var dta = snapshot.val();
        console.log("abc",dta);
      });

      


    window.onload = function() 
    {
      drawChart();
    };