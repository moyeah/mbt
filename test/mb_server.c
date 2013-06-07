static void
init_sockaddr (struct sockaddr_in *name,
               const char         *hostname,
               uint16_t            port)
{
  struct hostent *hostinfo;

  name->sin_family = AF_INET;
  name->sin_port = htons (port);
  hostinfo = gethostbyname (hostname);
  if (hostinfo == NULL)
  {
    fprintf (stderr, "Unkown host %s.\n", hostname);
    return;
  }
  name->sin_addr = *(struct in_addr *) hostinfo->h_addr;
}

int
mb_socket_client (const char *hostname, uint16_t port)
{
  int sockfd;
  struct sockaddr_in servername;

  /* Create socket */
  sockfd = socket (PF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror ("Socket (client)");
    return NULL;
  }

  /* Connect to server */
  init_sockaddr (&servername, hostname, port);
  if (0 > connect (sockfd,
                    (struct sockaddr *) &servername,
                    sizeof (servername)))
  {
    perror ("Connect (client)");
    return NULL;
  }

  return sockfd;
}

void
mb_socket_close (int sockfd)
{
  /* Close socket */
  close (sockfd);
}
