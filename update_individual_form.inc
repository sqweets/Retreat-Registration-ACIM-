<?php

/**
 * This file contains the form for sending an update message to individuals.
 */

require_once("retreatform_defines.inc");
require_once("retreatform_mail.inc");
require_once("retreatform_database.inc");

function form_individual_email($form, &$form_state) {

  $form['info'] = array(
      '#markup' => t('Message to be sent to an individual registrant</br>Hold CTRL and click on each name to select multiple recipients'),
  );
  
  $form['name'] = array(
    '#title' => t('Names listing'),
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => all_registrants_by_last_name(),
    '#required' => TRUE,
  );

  $form['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#size' => 60,
    '#maxlength' => 60,
    '#required' => TRUE,
  );
  $form['from'] = array(
    '#type' => 'textfield',
    '#title' => t('Your Name and/or Title'),
    '#size' => 60,
    '#maxlength' => 60,
    '#required' => TRUE,
  );
  $form['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
  );

  $form['send_emails'] = array(
    '#type' => 'submit',
    '#value' => t('SEND message'),
    '#submit' => array('form_individual_email_submit'),
  );

  return $form;
}

/**
 * The submit handler.
 */
function form_individual_email_submit($form, &$form_state) {
  $msg_values = array('from' => $form_state['values']['from'],
                  'message' => $form_state['values']['message'],
                  'subject' => $form_state['values']['subject'],
                  );

  $existing_node = new stdClass();

  // Get the array of selected names and send each email
  $names = $form_state['values']['name'];
  foreach($names as $key => $value) {
    // Get the node of the selected registrants                  
    $existing_node = node_load($value);
    $msg_values['email'] = $existing_node->field_email_address[$existing_node->language][0]['value'];
    $msg_values['first'] = $existing_node->field_first_name[$existing_node->language][0]['value'];
    $msg_values['last'] = $existing_node->field_last_name[$existing_node->language][0]['value'];
      
    // Send email
    email_individual_send($msg_values);
  }
}




