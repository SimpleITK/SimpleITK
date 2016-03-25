//
// Custom Casts
//
namespace {
$(when measurements $(foreach measurements
$(if active and ( custom_cast or label_map ) then
OUT=[[
template<typename FilterType>
struct ${name}CustomCast
{
]]
if custom_cast then
OUT=OUT..[[
  template <typename T>
  static ${type} Helper( const T & value ) { return ${custom_cast}; }
]]
end
OUT=OUT..[[

  static ${type} CustomCast( const FilterType *f]]
if parameters then
  for inum=1,#parameters do
    OUT=OUT..', '..parameters[inum].type..' '..parameters[inum].name
  end
end
OUT=OUT..[[ )
  {
    return ]]
if custom_cast then
  OUT=OUT..[[${name}CustomCast::Helper(]]
end
if label_map then
  OUT=OUT..[[f->GetOutput()->GetLabelObject(label)->Get${name}()]]
else
  OUT=OUT..[[f->Get${name}(${parameters[1].name})]]
end
if custom_cast then
  OUT=OUT..')'
end
OUT=OUT..';'..[[

  }
};
]]
  end)))
}
