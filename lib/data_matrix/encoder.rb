# frozen_string_literal: true
# Encoder ext ruby method aliases
module DataMatrix
  # encoder class ruby extensions
  class Encoder
    alias to_str to_s
    alias to_a data

    class << self
      def encode_string(value)
        new(value)
      end
    end

    def length
      height * width
    end
    alias size length
  end
end
