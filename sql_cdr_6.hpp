#ifndef SQL_CDR_6_1346941712
#define SQL_CDR_6_1346941712

namespace cdr_oracle_loader
{
    char const sql_cdr_6[] =
        "insert into cdr_format_6_copy ("

        "hdcd_record_format"
        ", hdcd_cdr_received_from"
        ", hdcd_service_data"
        ", recc_cdr_number"
        ", recc_tts_server"
        ", prdn_cdr_number"
        ", prdn_db_number"
        ", cause_for_creation"
        ", lnci_long_call_indication"
        ", lnci_tt_closing_reason"
        ", lnci_long_call_start_time"
        ", bsrv_extension_indicator"
        ", bsrv_bearer_services"
        ", bsrv_extension_indicator_2"
        ", bsrv_teleservices"
        ", calling_number"
        ", called_number"
        ", msc_id"
        ", call_start_time"
        ", time_to_first_digit"
        ", time_to_last_digit"
        ", time_to_answer"
        ", call_duration"
        ", active_call_duration"
        ", procedure_reference"
        ", slrf_segment_reference"
        ", slrf_leg_reference"
        ", ceph_clearing_direction"
        ", ceph_call_end_phase"
        ", cfce_location"
        ", cfce_coding_standard"
        ", cfce_recommendation"
        ", cfce_cause_value"
        ", data_volume"
        ", time_zone_shift"
        ", service_id"
        ", tariff_relation_id"
        ", cost"
        ", discount_amount"
        ", calling_prefix_id"
        ", called_prefix_id"
        ", tax_amount"
        ", tax_percent"
        ", traffic_period_id"
        ", tax_recapitulation_id"
        ", number_of_units"
        ", rating_result"
        ", balance"
        ", balance_expire"
        ", first_call_flag"
        ", flag"
        ", roaming_type"
        ", is_friendly"
        ", olservice_type"
        ", tdc_id"
        ", tariff_plan_id"
        ", personal_account_number"
        ", currency_code"
        ", terminal_device_class_id"
        ", tariff_zone_id"
        ", calling_category"
        ", trig"
        ", actual_call_duration"
        ", setup_fee"
        ", buffer"

        ") values("

        ":hdcd_record_format<unsigned>"
        ", :hdcd_cdr_received_from<unsigned>"
        ", :hdcd_service_data<unsigned>"
        ", :recc_cdr_number<unsigned>"
        ", :recc_tts_server<unsigned>"
        ", :prdn_cdr_number<unsigned>"
        ", :prdn_db_number<unsigned>"
        ", :cause_for_creation<unsigned>"
        ", :lnci_long_call_indication<unsigned>"
        ", :lnci_tt_closing_reason<unsigned>"
        ", :lnci_long_call_start_time<unsigned>"
        ", :bsrv_extension_indicator<unsigned>"
        ", :bsrv_bearer_services<unsigned>"
        ", :bsrv_extension_indicator_2<unsigned>"
        ", :bsrv_teleservices<unsigned>"
        ", :calling_number<char[34]>"
        ", :called_number<char[34]>"
        ", :msc_id<char[34]>"
        ", :call_start_time<timestamp>"
        ", :time_to_first_digit<unsigned>"
        ", :time_to_last_digit<unsigned>"
        ", :time_to_answer<unsigned>"
        ", :call_duration<unsigned>"
        ", :active_call_duration<unsigned>"
        ", :procedure_reference<bigint>"
        ", :slrf_segment_reference<unsigned>"
        ", :slrf_leg_reference<unsigned>"
        ", :ceph_clearing_direction<unsigned>"
        ", :ceph_call_end_phase<unsigned>"
        ", :cfce_location<unsigned>"
        ", :cfce_coding_standard<unsigned>"
        ", :cfce_recommendation<unsigned>"
        ", :cfce_cause_value<unsigned>"
        ", :data_volume<unsigned>"
        ", :time_zone_shift<unsigned>"
        ", :service_id<unsigned>"
        ", :tariff_relation_id<unsigned>"
        ", :cost<bigint>"
        ", :discount_amount<bigint>"
        ", :calling_prefix_id<unsigned>"
        ", :called_prefix_id<unsigned>"
        ", :tax_amount<bigint>"
        ", :tax_percent<unsigned>"
        ", :traffic_period_id<unsigned>"
        ", :tax_recapitulation_id<unsigned>"
        ", :number_of_units<bigint>"
        ", :rating_result<unsigned>"
        ", :balance<bigint>"
        ", :balance_expire<timestamp>"
        ", :first_call_flag<unsigned>"
        ", :flag<unsigned>"
        ", :roaming_type<unsigned>"
        ", :is_friendly<unsigned>"
        ", :olservice_type<unsigned>"
        ", :tdc_id<bigint>"
        ", :tariff_plan_id<unsigned>"
        ", :personal_account_number<bigint>"
        ", :currency_code<char[4]>"
        ", :terminal_device_class_id<unsigned>"
        ", :tariff_zone_id<unsigned>"
        ", :calling_category<unsigned>"
        ", :trig<unsigned>"
        ", :actual_call_duration<unsigned>"
        ", :setup_fee<bigint>"
        ", :buffer<raw[1024]>"
        ")";
}

#endif // SQL_CDR_6_1346941712
