#!/usr/bin/env ruby

class Pgchk
  @MemTotal
  @MemFree
  @Buffers
  @Cached
  @SwapCached
  @Active
  @Inactive
  @LowFree
  @SwapFree
  @Dirty
  @Writeback
  @AnonPages
  @Mapped
  @Slab
  @PageTables
  @Committed_AS
  @VmallocUsed

  def read_mem_proc()
    f = open("/proc/meminfo")
    while line = f.gets
      if line =~ /^MemTotal/
          @MemTotal = line.split[1].to_i
      elsif line =~ /^MemFree/
          @MemFree = line.split[1].to_i
      elsif line =~ /^Buffers/
          @Buffers = line.split[1].to_i
      elsif line =~ /^Cached/
          @Cached = line.split[1].to_i
      elsif line =~ /^SwapCached/
          @SwapCached = line.split[1].to_i
      elsif line =~ /^Active/
          @Active = line.split[1].to_i
      elsif line =~ /^Inactive/
          @Inactive = line.split[1].to_i
      elsif line =~ /^LowFree/
          @LowFree = line.split[1].to_i
      elsif line =~ /^SwapFree/
          @SwapFree = line.split[1].to_i
      elsif line =~ /^Dirty/
          @Dirty = line.split[1].to_i
      elsif line =~ /^Writeback/
          @Writeback = line.split[1].to_i
      elsif line =~ /^AnonPages/
          @AnonPages = line.split[1].to_i
      elsif line =~ /^Mapped/
          @Mapped = line.split[1].to_i
      elsif line =~ /^Slab/
          @Slab = line.split[1].to_i
      elsif line =~ /^PageTables/
          @PageTables = line.split[1].to_i
      elsif line =~ /^Committed_AS/
          @Committed_AS = line.split[1].to_i
      elsif line =~ /^VmallocUsed/
          @VmallocUsed = line.split[1].to_i
      end
    end
    f.close
    printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
           @MemTotal, @MemFree, @Buffers, @Cached, @SwapCached,
           @Active, @Inactive, @LowFree, @SwapFree, @Dirty, @Writeback,
           @AnonPages, @Mapped, @Slab, @PageTables, @Committed_AS, @VmallocUsed)
  end
end

a = Pgchk.new
loop do
  a.read_mem_proc()
  sleep(0.1)
end
