<?php
/**
 * @file mylottery.rule.inc
 */
/**
 * Implementation of hook_rules_event_info().
 */
function mylottery_rules_event_info() {
  return array(
    'mylottery_check' => array(
      'label' => t('User visits lottery page for the first time'),
      'group' => t('Lottery'),
      'variables' => array(
        'account' => array('type' => 'user', 'label' => t('User_acc')),
      ),
    ),
  );
}
/**
 * Implements hook_rules_condition_info().
 */
function mylottery_rules_condition_info() {
  return array(
    'mylottery_user_has_role' => array(
      'label' => t('User has role(s)'),
      'parameter' => array(
        'account' => array('type' => 'user', 'label' => t('User')),
        'roles' => array(
          'type' => 'list<integer>',
          'label' => t('Roles'),
          'options list' => '_mylottery_user_roles_options_list',
        ),
        'operation' => array(
          'type' => 'text',
          'label' => t('Match roles'),
          'options list' => '_mylottery_user_condition_operations',
          'restriction' => 'input',
          'optional' => TRUE,
          'default value' => 'AND',
          'description' => t('If matching against all selected roles, the user must have <em>all</em> the roles selected.'),
        ),
      ),
      'group' => t('Lottery'),
      'base' => '_mylottery_condition_user_has_role',
    ),
  );
}
/**
 * Options list callback for user roles.
 */
function _mylottery_user_roles_options_list($element) {
  return entity_metadata_user_roles('roles', array(), $element instanceof RulesConditionInterface ? 'view' : 'edit');
}
function _mylottery_user_condition_operations() {
  return array(
    'AND' => t('all'),
    'OR' => t('any'),
  );
}

/**
 * Condition.
 * @param $account
 * @param $roles
 * @param string $operation
 * @return bool
 */
function _mylottery_condition_user_has_role($account, $roles, $operation = 'AND') {
  switch ($operation) {
    case 'OR':
      foreach ($roles as $rid) {
        if (isset($account->roles[$rid])) {
          return TRUE;
        }
      }
      return FALSE;
    case 'AND':
      foreach ($roles as $rid) {
        if (!isset($account->roles[$rid])) {
          return FALSE;
        }
      }
      return TRUE;
  }
}
/**
* Implements hook_rules_action_info() on behalf of the user module.
 */
function mylottery_rules_action_info() {
  $items = array(
    'mylottery_first_time_action' => array(
      'label' => t('Lottery first time action'),
      'parameter' => array(
        'message' => array(
          'type' => 'text',
          'label' => t('Lottery action first time'),
          'description' => t('Message to show.'),
        ),
        'message2' => array(
          'type' => 'text',
          'label' => t('Loss'),
          'description' => t('Message to show when loss.'),
        ),
        'account' => array(
          'type' => 'user',
          'label' => t('User'),
          'description' => t('who.'),
        ),
      ),
    'group' => t('Lottery'),
    'base' => 'mylottery_first_time_action',
    )
  );
  return $items;
}

/**
 * Implements Action function for custom rule.
 * @param $win
 * @param $loss
 * @param $user
 */
function mylottery_first_time_action($win, $loss, $user) {
  $cache = cache_get('mylottery_lottery_result_'.$user->uid, 'cache');
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    if($cache->data == XMLRPC_WIN_CODE){
      drupal_set_message($win, 'status');
    }
    else {
      drupal_set_message($loss, 'status');
    }
  }
  else {
    global $base_url;
    $server = url($base_url . '/xmlrpc.php', array('external' => TRUE));
    $xmlrpc_result = xmlrpc($server, array('mylottery.check' => array(rand(1,8))));
    $lottery_results = cache_get('mylottery_results_cache', 'cache');
    if(!empty($lottery_results)){
    $lottery_results = $lottery_results->data;
    }
    else {
      $lottery_results = array();
    }
    if($xmlrpc_result == XMLRPC_WIN_CODE) {
      $lottery_results[] = _lottery_result_cache_forming($user, $xmlrpc_result);
      cache_set('mylottery_lottery_result_'.$user->uid, XMLRPC_WIN_CODE ,'cache', CACHE_PERMANENT);
      drupal_set_message($win, 'status');
    }
    else {
      $lottery_results[] = _lottery_result_cache_forming($user,  $xmlrpc_result);
      cache_set('mylottery_lottery_result_'.$user->uid, XMLRPC_LOSS_CODE ,'cache', CACHE_PERMANENT);
      drupal_set_message($loss, 'status');
    }
    cache_set('mylottery_results_cache',  $lottery_results, 'cache', CACHE_TEMPORARY);
  }
}
/**
 * Helper function to list item for lottery block
 * @param $user
 * @param $code
 * @return null|string
 */
function _lottery_result_cache_forming($user, $code) {
  $result = ($code == XMLRPC_WIN_CODE) ? t('Won'): t('Loss');
  $datetime = format_date(REQUEST_TIME, 'custom','d-m-Y H:i');
  return t('!datetime !name !result.', array('!name' => $user->name, '!datetime' => $datetime, '!result' => $result));
}
