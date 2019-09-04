<?php

/**
 * This file contains the form for resending the registration emails.
 */

require_once("retreatform_defines.inc");
require_once("retreatform_mail.inc");
require_once("retreatform_utilities.inc");
  
function form_email_resend($form, &$form_state) {
  $form['first'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#size' => 60,
    '#maxlength' => 25,
    '#required' => TRUE,
    '#default_value' => t(''),
  );
  $form['last'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#size' => 60,
    '#maxlength' => 25,
    '#required' => TRUE,
    '#default_value' => t(''),
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 40,
    '#maxlength' => 40,
    '#description' => t('Make sure the registration email is updated first, if necessary.'),
    '#required' => TRUE,
    '#default_value' => t(''),
  );
  $form['next_one'] = array(
    '#type' => 'submit',
    '#value' => t('Resend Email(s)'),
    '#validate' => array('form_email_resend_validate'),
    '#submit' => array('form_email_resend_submit'),
  );

  return $form;
}

/**
 * Validate handler for the submit.
 */
function form_email_resend_validate($form, &$form_state) {
  $email = $form_state['values']['email'];
  if (!valid_email_address($email)) {
    form_set_error('email', t('Please enter a valid email address.'));
  }
}

/**
 * The submit handler.
 */
function form_email_resend_submit($form, &$form_state) {
  $page_one_values = array();
  $page_two_values = array();

  // Find the entry in the database
  $option_items_nids = array();
  $option_items = array();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_first_name', 'value', $form_state['values']['first'], '=')
    ->fieldCondition('field_last_name', 'value', $form_state['values']['last'], '=')
    ->fieldCondition('field_email_address', 'value', $form_state['values']['email'], '=');
 
  $result = $query->execute();
  if (isset($result['node'])) {
    $option_items_nids = array_keys($result['node']);
    $option_items = entity_load('node', $option_items_nids);
  } else {
    drupal_set_message(t('No registrations matched the first name, last name and email address entered.'), 'error');
  }
 
  // Create a node object
  $node = new stdClass();
  $node->language = LANGUAGE_NONE;

  foreach($option_items as $key => $value) {
    $node = node_load($key);

    $page_one_values['first']   = $node->field_first_name[$node->language][0]['value'];    
    $page_one_values['last']    = $node->field_last_name[$node->language][0]['value'];     
    $page_one_values['address'] = $node->field_address[$node->language][0]['value'];

    if (isset($node->field_address_2[$node->language])) {
      $page_one_values['address2']         = $node->field_address_2[$node->language][0]['value'];
    } else {
      $page_one_values['address2']         = NULL;
    }
    $page_one_values['city']              = $node->field_city[$node->language][0]['value'];          
    $page_one_values['state']             = $node->field_state[$node->language][0]['value'];         
    $page_one_values['zip_code']          = $node->field_zip_code[$node->language][0]['value'];      
    $page_one_values['phone']             = $node->field_phone_number[$node->language][0]['value'];  
    $page_one_values['email']             = $node->field_email_address[$node->language][0]['value']; 
    $page_two_values['option']            = $node->field_room_option[$node->language][0]['value'];   
    $page_two_values['roommate']          = $node->field_roommate[$node->language][0]['value'];      
    $page_two_values['meal']              = $node->field_meal_needs[$node->language][0]['value'];
    $page_two_values['special_needs']     = $node->field_special_needs[$node->language][0]['value'];
    $page_two_values['first_retreat']     = $node->field_first_retreat[$node->language][0]['value'];

    if (isset($node->field_meal_info[$node->language])) {
      $page_two_values['meal_details']     = $node->field_meal_info[$node->language][0]['value'];     
    } else {
      $page_two_values['meal_details']     = NULL;     
    }
    $page_two_values['special_needs']    = $node->field_special_needs[$node->language][0]['value'];    

    if (isset($node->field_needs_info[$node->language])) {
      $page_two_values['needs_info']       = $node->field_needs_info[$node->language][0]['value'];     
    } else {
      $page_two_values['needs_info']       = NULL;     
    }
    $page_two_values['donation']         = $node->field_donation[$node->language][0]['value'];      
    $page_two_values['form_of_payment']  = $node->field_form_payment[$node->language][0]['value'];

    $form_state['page_values'][1] = $page_one_values;    
    $form_state['page_values'][2] = $page_two_values;    
    
    // Send out confirmation email
    email_confirm_send($form_state['page_values']);
    
    // Send form email
    if ($page_two_values['form_of_payment'] == 'Mail') {
      email_form_send($form_state['page_values']);
    }
  }
}


