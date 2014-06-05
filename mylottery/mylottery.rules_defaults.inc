<?php
/**
 * @file mylottery.rule_defaults.inc
 */
function mylottery_default_rules_configuration() {
  $configs = array();
  $rule = '{ "rules_test_rule" : {
    "LABEL" : "test_rule",
    "PLUGIN" : "reaction rule",
    "OWNER" : "rules",
    "REQUIRES" : [ "mylottery", "rules" ],
    "ON" : { "mylottery_check" : [] },
    "IF" : [
      { "mylottery_user_has_role" : { "account" : [ "account" ], "roles" : { "value" : { "2" : "2" } } } }
    ],
    "DO" : [
      { "mylottery_first_time_action" : {
        "message" : "You won, [account:name]!",
          "message2" : "You loose!",
          "account" : [ "account" ]
        }
      }
    ]
  }
}';
  $configs['rules_test_rule'] = rules_import($rule);
  return $configs;
}