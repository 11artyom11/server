#ifndef __EVENTS_H__
#define __EVENTS_H__


class CustomEvents : public QObject
{
    Q_OBJECT

public:
    CustomEvents();

signals:
   void connection_state_changed();
   void server_connection_not_responding ();

private:

};

#endif /* __EVENTS_H__ */
