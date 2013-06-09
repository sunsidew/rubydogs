require 'test_helper'

class KctControllerTest < ActionController::TestCase
  test "should get input" do
    get :input
    assert_response :success
  end

  test "should get webparse" do
    get :webparse
    assert_response :success
  end

  test "should get putdata" do
    get :putdata
    assert_response :success
  end

end
