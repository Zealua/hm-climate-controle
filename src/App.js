import React, { useRef, useState } from 'react';
import './App.css';

import Temperature from './components/pages/temperature';

import firebase from 'firebase/app';
import 'firebase/firestore';
import 'firebase/auth';
import 'firebase/analytics';
import 'firebase/database'

import { useAuthState } from 'react-firebase-hooks/auth';
import { useCollectionData } from 'react-firebase-hooks/firestore';

firebase.initializeApp({
  apiKey: "AIzaSyA1k22srU72gr3-ArItp18B89lGP8wGP6E",
  authDomain: "hmclimatecontrol.firebaseapp.com",
  databaseURL: "https://hmclimatecontrol-default-rtdb.firebaseio.com",
  projectId: "hmclimatecontrol",
  storageBucket: "hmclimatecontrol.appspot.com",
  messagingSenderId: "437814839046",
  appId: "1:437814839046:web:2439a7fc878f6baf2bc087",
  measurementId: "G-J3N8KKTNWZ"
})

const auth = firebase.auth();
// const fireRtDB = firebase.database();
const firestore = firebase.firestore();
const analytics = firebase.analytics();
// const rootRef = firebase.database();


function App() {

  const [user] = useAuthState(auth);

  return (
    <div className="App">
      <header>
        <h1></h1>
        <SignOut />
      </header>

      <section>
        {/* <ShowData/> */}
        {user ? <Temperature /> : <SignIn />}
      </section>

    </div>
  );
}

function SignIn() {

  const signInWithGoogle = () => {
    const provider = new firebase.auth.GoogleAuthProvider();
    auth.signInWithPopup(provider);
  }

  return (
    <>
      <button className="sign-in" onClick={signInWithGoogle}>Sign in with Google</button>
      <p>Do not violate the community guidelines or you will be banned for life!</p>
    </>
  )

}

function SignOut() {
  return auth.currentUser && (
    <button className="sign-out" onClick={() => auth.signOut()}>Sign Out</button>
  )
}

// function ShowData() {
//   var ref = rootRef.ref('Security');
//   ref.once("value").then(function(snapshot) {
//     snapshot.forEach(function(childSnapshot) {
//       var key = childSnapshot.key;
//       console.log('key:' + key);
//       var childData = childSnapshot.val();
//       console.log('child: ' + childData);
//     });
//   });
//   return (<><div id="zea+"/></>);
// }


function ChatRoom() {
  const dummy = useRef();
  console.log(firebase.auth().currentUser);
  // const security = fireRtDB.goOnline()
  const messagesRef = firestore.collection('messages');
  const query = messagesRef.orderBy('createdAt').limit(25);

  const [messages] = useCollectionData(query, { idField: 'id' });

  const [formValue, setFormValue] = useState('');


  const sendMessage = async (e) => {
    e.preventDefault();

    const { uid, photoURL } = auth.currentUser;

    await messagesRef.add({
      text: formValue,
      createdAt: firebase.firestore.FieldValue.serverTimestamp(),
      uid,
      photoURL
    })

    setFormValue('');
    dummy.current.scrollIntoView({ behavior: 'smooth' });
  }

  return (<>
    <main>

      {messages && messages.map(msg => <ChatMessage key={msg.id} message={msg} />)}

      <span ref={dummy}></span>

    </main>

    <form onSubmit={sendMessage}>

      <input value={formValue} onChange={(e) => setFormValue(e.target.value)} placeholder="say something nice" />

      <button type="submit" disabled={!formValue}>🕊️</button>

    </form>
  </>)
}


function ChatMessage(props) {
  const { text, uid, photoURL } = props.message;

  const messageClass = uid === auth.currentUser.uid ? 'sent' : 'received';

  return (<>
    <div className={`message ${messageClass}`}>
      <img src={photoURL || 'https://api.adorable.io/avatars/23/abott@adorable.png'} />
      <p>{text}</p>
    </div>
  </>)
}


export default App;