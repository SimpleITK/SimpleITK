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
  template <typename T>
]]
if custom_cast then
OUT=OUT..[[
  static ${type} Helper( const T & value ) { return ${custom_cast}; }
]]
else
OUT=OUT..[[
  static const ${type} &Helper( const T & value ) { return value; }
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
    return ${name}CustomCast::Helper(f]]

if label_map then
  OUT=OUT..[[->GetOutput()->GetLabelObject(label)->Get${name}()]]
else
  OUT=OUT..[[->Get${name}(label)]]
end
OUT=OUT..');'..[[

  }
};
]]
  end)))
}
