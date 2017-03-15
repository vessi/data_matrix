# frozen_string_literal: true
require 'spec_helper'

RSpec.describe DataMatrix::Encoder do
  it 'should provide correct encoding string' do
    expect(described_class.new('http://localhost').encoding).to eq('AAAAAAAATTTTTTTTT')
  end

  it 'should provide correct data matrix' do
    sample = %w(
      101010101010101010
      101101110101011011
      111000001100111000
      110111110101111011
      110001101110110100
      111101011100011001
      100000010000111000
      110101110110110111
      100110001000010000
      111001001101100111
      110101010111011000
      111110001101001011
      111110101111110100
      110001111000001101
      110011001010011010
      100011101111100011
      100110010110010010
      111111111111111111
    )
    expect(described_class.new('http://localhost').to_s.split(',')).to eq(sample)
  end
end
