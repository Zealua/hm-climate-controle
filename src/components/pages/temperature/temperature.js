import React, { Component } from 'react';

import { Line } from 'react-chartjs-2';


import firebase from 'firebase/app';
import 'firebase/auth';
import 'firebase/database';



  firebase.initializeApp({
    apiKey: "AIzaSyA1k22srU72gr3-ArItp18B89lGP8wGP6E",
    authDomain: "hmclimatecontrol.firebaseapp.com",
    databaseURL: "https://hmclimatecontrol-default-rtdb.firebaseio.com",
    projectId: "hmclimatecontrol",
    storageBucket: "hmclimatecontrol.appspot.com",
    messagingSenderId: "437814839046",
    appId: "1:437814839046:web:2439a7fc878f6baf2bc087",
    measurementId: "G-J3N8KKTNWZ"
  }, 'otherApp')

// const auth = firebase.auth();
const otherApp = firebase.app('otherApp');
// const databaseForOtherApp = firebase.database(otherApp);
const rootRef = firebase.database(otherApp);

export default class Temperature extends Component {

  constructor(props) {
    super(props);
    this.state = {listTempr: null,
      listLabels: null};
    this.updateData = this.updateData.bind(this);
  }

  componentDidMount() {
    this.updateData();
  }

  // updateTempr(data){
  //   this.setState({listTempr:data});
  // }
  // updateLabels (data){
  //   this.setState({listLabels:data});
  // }

  updateData  () {
    const path = "testDevice";//this.props.path;
    const fullWidth = {width : "80%", margin: "5%"};
    let listChild=[];
    let lebles=[]; let leblesF = [];
    let tempr = []; let temprF =[];
    let time = new Date(); 
    var ref = rootRef.ref(path);
    ref.once("value").then((snapshot) => {
      snapshot.forEach(function(childSnapshot) {
        listChild.push(childSnapshot.val());
      });
      // console.log('-------------------------------------------------------')
      console.log(listChild.length);
      for(let i=1;i<50;i++){
          tempr.push(listChild.at(0-i));
          time.setMinutes(time.getMinutes()-15);
          lebles.push(time.toLocaleTimeString());
      }
      for(let i=1; i<tempr.length; i++){
          temprF.push(tempr.at(0-i));
          leblesF.push(lebles.at(0-i));
      }
    
    console.log(lebles);
    console.log(tempr);
    this.setState({listTempr:tempr});
    this.setState({listLabels:lebles});
    }    
    );

  }

   render() {
      const listLabels = this.state.listLabels;
      const listTempr = this.state.listTempr;
    return (
      <div className="zeal">
           <Line
              data={{
                labels: listLabels,
                datasets: [
                  {
                    data: listTempr,
                    label: "Activity",
                    borderColor: "#3333ff",
                    fill: true,
                    backgroundColor: "#CAA6DB",
                  },
                ],
              }}
            />
      </div>
    )
  }
}
