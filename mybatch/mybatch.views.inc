<?php
function mybatch_views_data(){
  $data['mybatch_table']['table']['group'] = t('Currencies');
  $data['mybatch_table']['table']['base'] = array(
    'field' => 'id', // This is the identifier field for the view.
    'title' => t('Currencies table'),
    'help' => t('Example table contains example content and can be related to nodes.'),
    'weight' => -10,
  );
  $data['mybatch_table']['id'] = array(
    'title' => 'Id',
    'group' => t('Currencies'),
    'help' => t('Currency Id'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  $data['mybatch_table']['rate'] = array(
    'title' => 'Rate',
    'group' => t('Currencies'),
    'help' => t('Currency Rate'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  $data['mybatch_table']['charcode'] = array(
    'title' => t('Charcode'),
    'group' => t('Currencies'),
    'help' => t('Char code field.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  $data['mybatch_table']['name'] = array(
    'title' => t('Name'),
    'group' => t('Currencies'),
    'help' => t('Name field.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  return $data;
}