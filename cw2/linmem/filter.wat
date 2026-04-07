(module
  (type (;0;) (func (param i32 i32)))
  (func (;0;) (type 0) (param i32 i32)
    (local i32)
    local.get 0
    local.get 1
    i32.mul
    local.set 0
    loop  ;; label = @1
      local.get 0
      local.get 2
      i32.gt_s
      if  ;; label = @2
        local.get 2
        i32.const 2
        i32.shl
        local.tee 1
        i32.const 255
        local.get 1
        i32.load8_u
        i32.sub
        i32.store8
        local.get 1
        i32.const 1
        i32.add
        i32.const 255
        local.get 1
        i32.load8_u offset=1
        i32.sub
        i32.store8
        local.get 1
        i32.const 2
        i32.add
        i32.const 255
        local.get 1
        i32.load8_u offset=2
        i32.sub
        i32.store8
        local.get 2
        i32.const 1
        i32.add
        local.set 2
        br 1 (;@1;)
      end
    end)
  (memory (;0;) 1)
  (export "invertColors" (func 0))
  (export "memory" (memory 0)))
