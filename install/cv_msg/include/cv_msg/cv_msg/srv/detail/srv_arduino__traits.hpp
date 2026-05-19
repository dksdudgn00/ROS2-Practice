// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cv_msg:srv/SrvArduino.idl
// generated code does not contain a copyright notice

#ifndef CV_MSG__SRV__DETAIL__SRV_ARDUINO__TRAITS_HPP_
#define CV_MSG__SRV__DETAIL__SRV_ARDUINO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cv_msg/srv/detail/srv_arduino__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cv_msg
{

namespace srv
{

inline void to_flow_style_yaml(
  const SrvArduino_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: dir
  {
    out << "dir: ";
    rosidl_generator_traits::value_to_yaml(msg.dir, out);
    out << ", ";
  }

  // member: speed
  {
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SrvArduino_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: dir
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dir: ";
    rosidl_generator_traits::value_to_yaml(msg.dir, out);
    out << "\n";
  }

  // member: speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SrvArduino_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace cv_msg

namespace rosidl_generator_traits
{

[[deprecated("use cv_msg::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cv_msg::srv::SrvArduino_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  cv_msg::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cv_msg::srv::to_yaml() instead")]]
inline std::string to_yaml(const cv_msg::srv::SrvArduino_Request & msg)
{
  return cv_msg::srv::to_yaml(msg);
}

template<>
inline const char * data_type<cv_msg::srv::SrvArduino_Request>()
{
  return "cv_msg::srv::SrvArduino_Request";
}

template<>
inline const char * name<cv_msg::srv::SrvArduino_Request>()
{
  return "cv_msg/srv/SrvArduino_Request";
}

template<>
struct has_fixed_size<cv_msg::srv::SrvArduino_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<cv_msg::srv::SrvArduino_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<cv_msg::srv::SrvArduino_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace cv_msg
{

namespace srv
{

inline void to_flow_style_yaml(
  const SrvArduino_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: answer
  {
    out << "answer: ";
    rosidl_generator_traits::value_to_yaml(msg.answer, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SrvArduino_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: answer
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "answer: ";
    rosidl_generator_traits::value_to_yaml(msg.answer, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SrvArduino_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace cv_msg

namespace rosidl_generator_traits
{

[[deprecated("use cv_msg::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cv_msg::srv::SrvArduino_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  cv_msg::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cv_msg::srv::to_yaml() instead")]]
inline std::string to_yaml(const cv_msg::srv::SrvArduino_Response & msg)
{
  return cv_msg::srv::to_yaml(msg);
}

template<>
inline const char * data_type<cv_msg::srv::SrvArduino_Response>()
{
  return "cv_msg::srv::SrvArduino_Response";
}

template<>
inline const char * name<cv_msg::srv::SrvArduino_Response>()
{
  return "cv_msg/srv/SrvArduino_Response";
}

template<>
struct has_fixed_size<cv_msg::srv::SrvArduino_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<cv_msg::srv::SrvArduino_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<cv_msg::srv::SrvArduino_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<cv_msg::srv::SrvArduino>()
{
  return "cv_msg::srv::SrvArduino";
}

template<>
inline const char * name<cv_msg::srv::SrvArduino>()
{
  return "cv_msg/srv/SrvArduino";
}

template<>
struct has_fixed_size<cv_msg::srv::SrvArduino>
  : std::integral_constant<
    bool,
    has_fixed_size<cv_msg::srv::SrvArduino_Request>::value &&
    has_fixed_size<cv_msg::srv::SrvArduino_Response>::value
  >
{
};

template<>
struct has_bounded_size<cv_msg::srv::SrvArduino>
  : std::integral_constant<
    bool,
    has_bounded_size<cv_msg::srv::SrvArduino_Request>::value &&
    has_bounded_size<cv_msg::srv::SrvArduino_Response>::value
  >
{
};

template<>
struct is_service<cv_msg::srv::SrvArduino>
  : std::true_type
{
};

template<>
struct is_service_request<cv_msg::srv::SrvArduino_Request>
  : std::true_type
{
};

template<>
struct is_service_response<cv_msg::srv::SrvArduino_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // CV_MSG__SRV__DETAIL__SRV_ARDUINO__TRAITS_HPP_
