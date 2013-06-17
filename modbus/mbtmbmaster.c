#include "config.h"

#include "mbtmbmaster.h"

#define MBT_MB_MASTER_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), MBT_TYPE_MB_MASTER, MbtMBMaterPrivate))

struct _MbtMBMasterPrivate
{
  gchar *name;

  guint  mode;
};

enum {
  PROP_0,

  PROP_NAME,
  PROP_MODE,

  N_PROPERTIES
};

static void mbt_mb_master_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec    pspec);
static void mbt_mb_master_get_property (GObject      *object,
                                        guint         prop_id,
                                        GValue       *value,
                                        GParamSpec    pspec);
static void mbt_mb_master_finalize     (GObject      *object);

static void mbt_mb_master_set_name_internal (MbtMBMaster *mb_master,
                                             gchar       *name);

G_DEFINE_TYPE (MbtMBMaster, mbt_mb_master, G_TYPE_OBJECT);

static void
mbt_mb_master_class_init (MbtMBMasterClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->set_property = mbt_mb_master_set_property;
  gobject_class->get_property = mbt_mb_master_get_property;
  gobject_class->finalize = mbt_mb_master_finalize;

  g_object_class_install_property (gobject_class,
                                   PROP_NAME,
                                   g_param_spec_string ("name",
                                                        P_("Name"),
                                                        P_("Master's name"),
                                                        MBT_TYPE_MB_MODE,
                                                        MBT_MB_TCPIP,
                                                        G_PARAM_READWRITE);

  g_object_class_install_property (gobject_class,
                                   PROP_MODE,
                                   g_param_spec_enum ("mode",
                                                      P_("Mode"),
                                                      P_("Mode type"),
                                                      "",
                                                      G_PARAM_READWRITE);

  g_type_class_add_private (klass, sizeof (MbtMBMasterPrivate));
}

static void
mbt_mb_master_set_property (GObject      *object,
                            guint         prop_id,
                            const GValue *value,
                            GParamSpec   *pspec)
{
  MbtMBMaster *mb_master = MBT_MB_MASTER (object);

  switch (prop_id)
    {
    case PROP_NAME:
      mbt_mb_master_set_name (mb_master, g_value_get_string (value));
      break;

    case PROP_MODE:
      mbt_mb_master_set_mode (mb_master, g_value_get_enum (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
mbt_mb_master_get_property (GObject    *object,
                            guint       prop_id,
                            GValue     *value,
                            GParamSpec *pspec)
{
  MbtMBMaster *mb_master = MBT_MB_MASTER (object);
  MbtMBMasterPrivate *priv = mb_master->priv;

  switch (prop_id)
    {
    case PROP_NAME:
      g_value_set_string (value, priv->name);
      break;

    case PROP_MODE:
      g_value_set_enum (value, priv->mode);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
mbt_mb_master_init (MbtMBMaster *mb_master)
{
  MbtMBMasterPrivate *priv;

  mb_master->priv = MBT_MB_MASTER_GET_PRIVATE (mb_master);
  priv = mb_master->priv;

  priv->mode = MBT_MB_RTU;

  mbt_mb_master_set_name (mb_master, "");
}

static void
mbt_mb_master_finalize (GObject *object)
{
  MbtMBMaster *mb_master = MBT_MB_MASTER (gobject);
  MbtMBMasterPrivate *priv = mb_master->priv;

  g_free (priv->name);
  g_free (priv->mode);

  G_OBJECT (mbt_mb_master_parent_class)->finalize (gobject);
}

static void
mbt_mb_master_set_name_internal (MbtMBMaster *mb_master,
                                 gchar       *name)
{
  MbtMBMasterPrivate *priv = mb_master->priv;

  g_free (priv->name);

  priv->name = name;

  g_object_notify (G_OBJECT (mb_master), "name");
}

MbtMBMaster*
mbt_mb_master_new (const gchar *name)
{
  MbtMBMaster *mb_master = g_object_new (MBT_MB_MASTER, NULL);

  if (name && *name)
    mbt_mb_master_set_name (mb_master, name);

  return mb_master;
}

void
mbt_mb_master_set_name (MbtMBMaster *mb_master,
                        const gchar *name)
{
  g_return_if_fail (MBT_IS_MB_MASTER (mb_master));

  g_object_freeze_notify (G_OBJECT (name));

  mbt_mb_master_set_name_internal (label, g_strdup (name ? name : ""));

  g_object_thaw_notify (G_OBJECT (mb_master));
}

const gchar*
mbt_mb_master_get_name (MbtMBMaster *mb_master)
{
  g_return_val_if_fail (MBT_MB_MASTER (mb_master), NULL);

  return mb_master->priv->name;
}

void
mbt_mb_master_set_mode (MbtMBMaster *mb_master,
                        MbtMBMode    mode)
{
  g_return_if_fail (MBT_IS_MB_MASTER (mb_master));
  g_return_if_fail (MBT_IS_MB_MODE (mode));

  MbtMBMasterPrivate *priv = mb_master->priv;

  if ((MbtMBMode) priv->mode != mode)
    {
      priv->mode = mode;

      g_object_notify (G_OBJECT (mb_master), "mode");
    }
}

MbtMBMode
mbt_mb_master_get_mode (MbtMBMaster *mb_master)
{
  g_return_val_if_fail (MBT_IS_MB_MASTER (mb_master), 0);

  return mb_master->priv->mode;
}