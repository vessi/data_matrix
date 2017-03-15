# frozen_string_literal: true
# Encoder ext ruby method aliases
module DataMatrix
  # encoder class ruby extensions
  class Encoder
    alias to_str to_s
    alias to_a data

    def length
      height * width
    end
    alias size length
  end
end
