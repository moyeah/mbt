#include "config.h"

#include "mbtmb.h"

struct _MbtMBPrivate
{
  gchar *tag;
};

enum {
  PROP_0,

  PROP_TAG,

  N_PROPERTIES
};

static void mbt_mb_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec);
static void mbt_mb_get_property (GObject      *object,
                                 guint         prop_id,
                                 GValue       *value,
                                 GParamSpec   *pspec);
static void mbt_mb_finalize     (GObject      *object);

static void mbt_mb_set_tag_internal (MbtMB *mb,
                                     gchar *tag);

G_DEFINE_TYPE (MbtMB, mbt_mb, G_TYPE_OBJECT);

static void
mbt_mb_class_init (MbtMBClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->set_property = mbt_mb_set_property;
  gobject_class->get_property = mbt_mb_get_property;
  gobject_class->finalize = mbt_mb_finalize;

  g_object_class_install_property (gobject_class,
                                   PROP_TAG,
                                   g_param_spec_string ("tag",
                                                        _("TAG"),
                                                        _("Object\'s TAG"),
                                                        NULL,
                                                        G_PARAM_READWRITE));

  g_type_class_add_private (klass, sizeof (MbtMBPrivate));
}

static void
mbt_mb_set_property (GObject      *object,
                     guint         prop_id,
                     const GValue *value,
                     GParamSpec   *pspec)
{
  MbtMB *mb = MBT_MB (object);

  switch (prop_id)
    {
    case PROP_TAG:
      mbt_mb_set_tag (mb, g_value_get_string (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
mbt_mb_get_property (GObject    *object,
                     guint       prop_id,
                     GValue     *value,
                     GParamSpec *pspec)
{
  MbtMB *mb = MBT_MB (object);
  MbtMBPrivate *priv = mb->priv;

  switch (prop_id)
    {
    case PROP_TAG:
      g_value_set_string (value, priv->tag);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
mbt_mb_init (MbtMB *mb)
{
  MbtMBPrivate *priv;

  mb->priv = G_TYPE_INSTANCE_GET_PRIVATE (mb,
                                          MBT_TYPE_MB,
                                          MbtMBPrivate);

  priv = mb->priv;

  mbt_mb_set_tag (mb, NULL);
}

static void
mbt_mb_finalize (GObject *object)
{
  MbtMB *mb = MBT_MB (object);
  MbtMBPrivate *priv = mb->priv;

  g_free (priv->tag);

  G_OBJECT_CLASS (mbt_mb_parent_class)->finalize (object);
}

static void
mbt_mb_set_tag_internal (MbtMB *mb,
                         gchar *tag)
{
  MbtMBPrivate *priv = mb->priv;

  g_free (priv->tag);

  priv->tag = tag;

  g_object_notify (G_OBJECT (mb), "tag");
}

MbtMB*
mbt_mb_new (const gchar *tag)
{
  MbtMB *mb = g_object_new (MBT_TYPE_MB, NULL);

  if (tag && *tag)
    mbt_mb_set_tag (mb, tag);

  return mb;
}

void
mbt_mb_set_tag (MbtMB       *mb,
                const gchar *tag)
{
  g_return_if_fail (MBT_IS_MB (mb));

  g_object_freeze_notify (G_OBJECT (mb));

  mbt_mb_set_tag_internal (mb, g_strdup (tag ? tag : ""));

  g_object_thaw_notify (G_OBJECT (mb));
}

const gchar*
mbt_mb_get_tag (MbtMB *mb)
{
  g_return_val_if_fail (MBT_MB (mb), NULL);

  return mb->priv->tag;
}