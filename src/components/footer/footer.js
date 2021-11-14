import React from 'react';

import './footer.css';

const Footer = ({ onServiceChange }) => {
  return (
    <div className="container container-table mildle-all">
      <div className="row"> {/* vertical-center-row"> */}
        <div className="col-4"> 
          <p className="textFooter">
            <strong>Для зв'язку: </strong>
          </p>
          <p className="textFooter">si.a.pastry@gmail.com</p>
          <p className="textFooter">+38 097 077 22 72</p>
        </div>
        <div className="col-4"> 
            <p className="textFooter"><strong>
              Si.A pastry studio  
            </strong></p>
        </div>
        <div className="col-4"> 
          <p className="textFooter"><strong>
            Ми в соцмережах:
          </strong></p>
          <div className="btn-group" role="group" aria-label="Basic example">
            <a className="btn btn-secondary" href="https://www.facebook.com/si.a.pastry/"
                  target="_blank" rel="noopener noreferrer">
                    <span className="link" title="Ми в Facebook">F</span></a>
            <a className="btn btn-secondary" href="https://www.instagram.com/si.a.pastry/"
                  target="_blank" rel="noopener noreferrer">
                    <span className="link" title="Ми в Instagram">I</span></a>
            <a className="btn btn-secondary" href="https://www.pinterest.com/pastry_studio/"
                  target="_blank" rel="noopener noreferrer" >
                    <span className="link" title="Ми в Pinterest">P</span></a>
            </div>
        </div>
      </div>
    </div>
  );
};

export default Footer;
