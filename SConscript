Import("env_etc")

env_etc.tnt_dist = env_etc.libtbx_env.dist_path("tnt")
env_etc.tnt_include = env_etc.norm_join(env_etc.tnt_dist, "include")

env_etc.tnt_common_includes = [
  env_etc.tnt_include,
  env_etc.libtbx_include,
  env_etc.scitbx_include,
  env_etc.boost_include,
]

Import("env_base", "env_etc")
env = env_base.Copy(
  CXXFLAGS=env_etc.cxxflags_base,
  LIBS=env_etc.libm,
  LIBPATH=["#libtbx"]
)
env_etc.include_registry.append(
  env=env,
  paths=env_etc.tnt_common_includes)

if (not env_etc.no_boost_python):
  Import("env_scitbx_boost_python_ext")
  env_bpl = env_scitbx_boost_python_ext.Copy()
  env_etc.include_registry.append(
    env=env_bpl,
    paths=env_etc.tnt_common_includes)
  env_bpl.SharedLibrary(
    target="#libtbx/tnt_ext",
    source=["tnt_ext.cpp"])
