classdef Monster < handle
    % c++ wrapper

properties (Access = private)
    id
end

methods
  function obj = Monster(filename)
  %DATABASE Create a new database.
    assert(ischar(filename));
    obj.id = Monster_('new', filename);
  end

  function delete(obj)
  %DELETE Destructor.
    Monster_('delete', obj.id);
  end

  function [] = attack(obj, power)
      disp('uoooooooooooooo');
      Monster_('attack', obj.id, power);

  end

  function [life] = get_life(obj)
      life = Monster_('get_life', obj.id);
  end
  function [] = set_matrix(obj, mat)
      Monster_('set_matrix', obj.id, mat);
  end
  function [] = set_vecmat(obj, mm)
      Monster_('set_vecmat', obj.id, mm);
  end
end

end
