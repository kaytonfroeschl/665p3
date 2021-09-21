set breakpoint pending on
set confirm off
file ./cshantyc
break cshanty::Err::report
commands
	where
end
break cshanty::InternalError::InternalError
commands
	where
end

define p3
  set args p3_tests/$arg0.cshanty -p --
  run
end
