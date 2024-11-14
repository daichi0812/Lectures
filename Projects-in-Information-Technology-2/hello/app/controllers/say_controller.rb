class SayController < ApplicationController
  def hello
    @time = Time.now
  end

  def goodbye
    @count = params[:count].to_i
    @count = 10 if @count <= 0
  end

  def advance_exercise
    @exp = params[:exponent].to_f
    if @exp.nil? || @exp <= 0
        @exp = 0.5 
    end
  end
end