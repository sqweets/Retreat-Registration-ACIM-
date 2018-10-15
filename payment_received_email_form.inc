<?php

/**
 * This file contains the form for sending a payment received message to the specified registrant.
 * NOTE: This is currently (as of 5/7/12) not being used but left in the project for historical purposes.
 */

require_once("retreatform_defines.inc");
require_once("retreatform_mail.inc");

function form_payment_received_email($form, &$form_state) {

  $form['info'] = array(
      '#markup' => t('Send payment received message'),
  );

  $form['first'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#size' => 60,
    '#maxlength' => 60,
    '#required' => TRUE,
  );
  $form['last'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#size' => 60,
    '#maxlength' => 60,
    '#required' => TRUE,
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 40,
    '#maxlength' => 40,
    '#required' => TRUE,
  );

  $form['send_emails'] = array(
    '#type' => 'submit',
    '#value' => t('SEND message'),
    '#validate' => array('form_payment_received_email_validate'),
    '#submit' => array('form_payment_received_email_submit'),
  );

  return $form;
}

/**
 * The validate handler.
 */
function form_payment_received_email_validate($form, &$form_state) {
  $email = $form_state['values']['email'];
  if (!valid_email_address($email)) {
    form_set_error('email', t('Please enter a valid email address.'));
  }
}

/**
 * The submit handler.
 */
function form_payment_received_email_submit($form, &$form_state) {
  $msg_values = array('first' => $form_state['values']['first'],
                      'email' => $form_state['values']['email']);
      
      // Send email
      email_payment_received_send($msg_values);
}




