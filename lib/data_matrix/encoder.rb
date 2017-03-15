# frozen_string_literal: true
# Encoder ext ruby method aliases
module DataMatrix
  # encoder class ruby extensions
  class Encoder
    alias to_str to_s
    alias to_a data

    def initialize(value)
      raise ArgumentError, 'Value must be convertible to string' unless value.respond_to?(:to_s)
      encode_string(value.to_s)
    end

    def length
      height * width
    end
    alias size length
  end
end
