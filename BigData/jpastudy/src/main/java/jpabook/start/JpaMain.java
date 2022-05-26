package jpabook.start;

import ch.qos.logback.classic.Level;
import com.mysql.cj.QueryResult;
import com.querydsl.core.BooleanBuilder;
import com.querydsl.core.QueryResults;
import com.querydsl.core.types.dsl.BooleanExpression;
import com.querydsl.jpa.impl.JPAQueryFactory;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.jpa.repository.config.EnableJpaAuditing;
import javax.persistence.*;
import java.sql.Timestamp;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;
import java.util.ListIterator;
import org.apache.log4j.Logger;


@EnableJpaAuditing
@SpringBootApplication
public class JpaMain {
    static EntityManagerFactory emf = Persistence.createEntityManagerFactory("jpabook");
    private Logger logger = Logger.getLogger(JpaMain.class);

    public static void main(String[] args) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();

        try {
            tx.begin();

            /*** 사전 데이터 생성 ***/
            createBeforeData();

            /*** 1. 사용자 생성 ***/
            //Users newuser = createUser("김다은", 22, "구미", "옥계동", "ASI|KR|KS010|GUMI");

            /*** 2. 사용자 정보 수정 ***/
//            Users findUser = em.find(Users.class, 256l);
//            findUser.setName("사용자명변경");
//            em.merge(findUser);
//            em.flush();

            /*** 3. 영화 조회 1 ***/
//            System.out.println("3. 영화 조회 1");
//            ShowMovieWithWorkedId(1l);

            /*** 4. 영화 조회 2 ***/
//            System.out.println("4. 영화 조회 2");
//            Workers director = new Directors();
//            //director.setName("봉준호");
//            Workers actor = new Actors();
//            actor.setName("송강호");
//            SimpleDateFormat testDtFormat = new SimpleDateFormat("yyyy-MM-dd");
//            //Date date = testDtFormat.parse("2019-05-30");
//            Date date = null;
//            findMovieWithWorkerOpeningDateRunningTime(director, actor, date);

            /*** 5. 영화 조회 3 ***/
//            System.out.println("5. 영화 조회 3");
//            int pagingSize = 2;
//            int page = 1;
//            findMovieWithPaging(page, pagingSize);

            /*** 6. 상영 정보 조회 ***/
//            System.out.println("6. 상영 정보 조회");
//            Screens findScreen = em.find(Screens.class, 75l);
//            showScreenwithSeat(findScreen);

            /*** 7. 예매 - 예매 전후 예매 내역 조회, 마지막 상영 정보 조회 ***/
//            System.out.println("7. 예매 ");
//            Users findUser2 = em.find(Users.class, 256l);
//            Screens findScreen2 = em.find(Screens.class, 75l);
//            Tickets findTicket1 = em.find(Tickets.class, 80l);
//            Tickets findTicket2 = em.find(Tickets.class, 81l);
//
//            //예매내역조회
//            showTicket(findTicket1);
//            userTicketing(findTicket1, findUser2);
//            showTicket(findTicket1);
//
//            showTicket(findTicket2);
//            userTicketing(findTicket2, findUser2);
//            showTicket(findTicket2);
//
//            showScreenwithSeat(findScreen2);

            /*** 8. 예매 취소 - 예매 취소 전후 예매 정보 조회, 그리고 상영 정보 조회 ***/
//            System.out.println("8. 예매 취소");
//            Screens findScreen3 = em.find(Screens.class, 75l);
//            Tickets findTicket3 = em.find(Tickets.class, 80l);
//             //예매 취소
//            System.out.println("예매 취소 전");
//            showTicket(findTicket3);
//            cancelTicking(findTicket3);
//            System.out.println("예매 취소 후");
//            showTicket(findTicket3);
//             //상영정보 조회
//            showScreenwithSeat(findScreen3);

            /*** 9. 예매 정보 조회  ***/
            //System.out.println("9. 예매 정보 조회");
            //Tickets findTicket4 = em.find(Tickets.class, 81l);
            //showTicket(findTicket4);

            /*** 10. 영속성 전이를 위한 삭제 ***/
//           //사용자 삭제
//            System.out.println("10. 영속성 전이를 위한 삭제");
//            Users findUser3 = em.find(Users.class, 256l);
//            removeUser(em, findUser3);
            //예매내역삭제확인
//            Screens findScreen3 = em.find(Screens.class, 75l);
//            showScreenwithSeat(findScreen3);
            tx.commit();

        } catch (Exception e) {
            e.printStackTrace();
            tx.rollback();
        } finally {
            em.close();
        }
        emf.close();
    }

    /* 사용자 생성 */
    static Users createUser(String name, Integer age, String city, String street, String zipCode) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        Users user = new Users();
        try {
            tx.begin();
            user.setName(name);
            user.setAge(age);
            user.setHomeAddress(new Address(city, street, zipCode));

            em.persist(user);
            tx.commit();

        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
        return user;
    }

    /* 영화 생성 */
    static Movies createMovie(String name, Date openingDate, Genre genre, int runningTime) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        Movies movie = new Movies();
        try {
            tx.begin();
            movie.setName(name);
            movie.setOpeningDate(openingDate);
            movie.setGenre(genre);
            movie.setRunningTime(runningTime);
            em.persist(movie);
            tx.commit();
        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
        return movie;
    }

    /* 감독 생성 */
    static Directors createDirector(String name, int age, String birthPlace) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        Directors director = new Directors();
        try {
            tx.begin();
            director.setName(name);
            director.setAge(age);
            director.setBirthPlace(birthPlace);
            em.persist(director);
            tx.commit();
        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
        return director;
    }

    /* 배우 생성 */
    static Actors createActor(String name, int age, int height, String instaId) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        Actors actor = new Actors();
        try {
            tx.begin();
            actor.setName(name);
            actor.setAge(age);
            actor.setHeight(height);
            actor.setInstaId(instaId);
            em.persist(actor);
            tx.commit();

        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
        return actor;
    }

    /* Movie_Worker 생성 */
    static Movie_Worker createMovieWorker(Role_Type role_type, Movies movie, Workers worker) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        Movie_Worker movie_worker = new Movie_Worker();
        try {
            tx.begin();
            movie_worker.setRole_type(role_type);
            movie_worker.setMovie(movie);
            movie_worker.setWorker(worker);
            em.persist(movie_worker);
            tx.commit();

        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
        return movie_worker;
    }

    /* 상영관 생성 */
    static Theaters createTheater(String name, int floor) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        Theaters theater = new Theaters();
        try {
            tx.begin();
            theater.setName(name);
            theater.setFloor(floor);
            em.persist(theater);
            tx.commit();

        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
        return theater;
    }

    /* 좌석 생성 */
    static Seats createSeat(int row, int column, String status, Theaters theaters) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        Seats seat = new Seats();
        try {
            tx.begin();
            seat.setRow(row);
            seat.setColumn(column);
            seat.setStatus(status);
            seat.setTheaters(theaters);
            em.persist(seat);
            tx.commit();
        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
        return seat;
    }

    /* 상영 생성 */
    static Screens createScreen(Theaters theater, Movies movie, Date startTime, Date endTime) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        Screens screen = new Screens();
        try {
            tx.begin();
            screen.setTheater(theater);
            screen.setMovie(movie);
            screen.setStartTime(startTime);
            screen.setEndTime(endTime);
            em.persist(screen);
            tx.commit();
        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
        return screen;
    }

    /* 상영과 티켓 생성 */
    static Screen_Seat createScreenSeat(Seats seat, Tickets ticket) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        Screen_Seat screen_seat = new Screen_Seat();
        try {
            tx.begin();
            screen_seat.setSeats(seat);
            screen_seat.setTickets(ticket);
            em.persist(screen_seat);
            tx.commit();
        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
        return screen_seat;
    }

    /* 티켓 생성 */
    static Tickets createTicket(Screens screen) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        Tickets ticket = new Tickets();
        try {
            tx.begin();
            ticket.setScreens(screen);
            em.persist(ticket);
            tx.commit();
        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
        return ticket;
    }

    /* 3번 영화 조회 */
    static void ShowMovieWithWorkedId(Long movieId) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        System.out.println();
        try {
            tx.begin();
            JPAQueryFactory query = new JPAQueryFactory(em);
            QMovies qMovie = new QMovies("m");
            QMovie_Worker qMW = new QMovie_Worker("w");
            List<Movie_Worker> movie_worker = query.selectFrom(qMW)
                    .join(qMW.movie, qMovie)
                    .where(qMovie.id.eq(movieId))
                    .fetch();
            movie_worker.get(0).getMovie().PrintInfo();
            movie_worker.stream().forEach(w -> w.PrintInfo());
            tx.commit();
        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
    }

    /* 영화의 배우 혹은 감독 확인 */
    private static BooleanExpression workerNameContain(Workers dire, Workers actor) {
        if (dire.getName() == null && actor.getName() == null) {
            return null;
        }
        else if(dire.getName() == null)
        {
            return QMovie_Worker.movie_Worker.worker.name.eq(actor.getName());
        }
        else if(actor.getName() == null)
        {
            return QMovie_Worker.movie_Worker.worker.name.eq(dire.getName());
        }
        else
        {
            return QMovie_Worker.movie_Worker.worker.name.eq(dire.getName())
                    .or(QMovie_Worker.movie_Worker.worker.name.eq(actor.getName()));
        }
    }

    /* 영화의 개봉일 확인 */
    private static BooleanExpression movieOpeningContain(Date param) {
        if (param == null) {
            return null;
        }
        return QMovie_Worker.movie_Worker.movie.openingDate.eq(param);
    }

    /* 날짜가 NULL이고 배우 감독의 값이 주어질 경우 배우와 감독이 각 가르키는 영화가 같은지 확인 */
    private static BooleanExpression eqMovieOfDireAndActor(Workers dire, Workers actor) {
        if (dire.getName() == null || actor.getName() == null) {
            return null;
        }
        QMovie_Worker qMW = new QMovie_Worker("mw");
        QWorkers qW = new QWorkers("w");
        EntityManager em = emf.createEntityManager();
        JPAQueryFactory query = new JPAQueryFactory(em);

        List<Movie_Worker> movie_worker = query.selectFrom(qMW)
                .leftJoin(qW)
                .on(qMW.worker.id.eq(qW.id))
                .where(qW.name.eq(dire.getName()).or(qW.name.eq(actor.getName())),
                        qMW.id.isNotNull())
                .fetch();

        if(movie_worker.size() < 2)
        {
            return QMovie_Worker.movie_Worker.worker.name.eq("0");
        }

        if(movie_worker.get(0).getMovie().getId() == movie_worker.get(1).getMovie().getId()) {
            return QMovie_Worker.movie_Worker.worker.name.eq(dire.getName());
        }
        else {
            return QMovie_Worker.movie_Worker.worker.name.eq("0");
        }
    }

    /* 날짜만 Null이 아닐 경우 같은 영화가 여러번 나오지 않도록 방지 */
    private static BooleanExpression onlyDateNotNull(Workers d, Workers a, Date date)
    {
        if(d.getName() == null && a.getName() == null && date != null)
        {
            return QMovie_Worker.movie_Worker.role_type.in(Role_Type.감독);
        }
        else
            return null;
    }

    /* 4번 영화 조회2 */
    static void findMovieWithWorkerOpeningDateRunningTime(Workers director, Workers actor, Date openingDate) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();

        try {
            tx.begin();
            JPAQueryFactory query = new JPAQueryFactory(em);
            QMovie_Worker qMW = QMovie_Worker.movie_Worker;

            List<Movie_Worker> movie_worker = query.selectFrom(qMW)
                    .where(workerNameContain(director, actor),
                            movieOpeningContain(openingDate),
                            eqMovieOfDireAndActor(director, actor),
                            onlyDateNotNull(director,actor,openingDate))
                    .fetch();

            //movie_worker.stream().forEach(m->m.getMovie().PrintInfo());
            if( movie_worker.size() < 1 ) {
                System.out.println("조건 만족 없음 !!!!!!!!!");
                return;
            }

            movie_worker.stream().forEach(mw->mw.getMovie().PrintInfo());
            System.out.println("!!!!!!!!!");
            tx.commit();

        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
    }

    /* 5번 영화 조회3 */
    static void findMovieWithPaging(int page, int pagingSize)
    {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();

        try {
            tx.begin();
            JPAQueryFactory query = new JPAQueryFactory(em);
            QMovies qMovie = new QMovies("m");
            QMovie_Worker qMW = new QMovie_Worker("w");

            List<Movies> movieList = query.selectFrom(qMovie)
                    .join(qMovie)
                    .offset(pagingSize*(page-1))
                    .limit(pagingSize)
                    .fetch();

            System.out.println("Page "+String.valueOf(page));

            ListIterator<Movies> it = movieList.listIterator();
            while(it.hasNext())
            {
                Movies m = it.next();
                List<Movie_Worker> movie_worker = query.selectFrom(qMW)
                        .leftJoin(qMovie).fetchJoin()
                        .on(qMovie.id.eq(qMW.id))
                        .where(qMW.movie.id.eq(m.getId()),
                                qMW.role_type.in(Role_Type.조연, Role_Type.주연))
                        .fetch();

                System.out.println(String.valueOf("영화"+it.nextIndex())+") "+m.getName());
                movie_worker.stream().forEach(w->System.out.print(w.getWorker().getName()+", "));
                System.out.println();
            }

            tx.commit();
        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
    }


    /* 6번 상영 정보 조회 */
    static void showScreenwithSeat(Screens screen) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        try {
            tx.begin();
            JPAQueryFactory query = new JPAQueryFactory(em);

            QScreens qscreens = new QScreens("sc");

            // 상영정보
            List<Screens> screens = query.selectFrom(qscreens)
                    .where(qscreens.id.eq(screen.getId()))
                    .fetch();

            System.out.println(">> 상영 정보 <<");
            screens.stream().forEach(sc-> sc.printInfo());

            // 총 좌석, 사용 가능 좌석
            QTickets qtickets = new QTickets("t");
            QScreen_Seat qscreen_seat = new QScreen_Seat("ss");
            QSeats qseats = new QSeats("se");
            List<Screen_Seat> screen_seat = query.selectFrom(qscreen_seat)
                    .join(qscreen_seat.tickets, qtickets)
                    .join(qtickets.screen, qscreens)
                    .where(qscreens.id.eq(screen.getId()))
                    .fetch();

            System.out.println(">> 총 좌석 <<");
            System.out.println("-".repeat(40));
            screen_seat.stream().forEach(m->m.getSeats().printInfo());
            System.out.println("-".repeat(40));

            List<Screen_Seat> screen_seat2 = query.selectFrom(qscreen_seat)
                    .rightJoin(qseats)
                    .on(qscreen_seat.seats.id.eq(qseats.id),
                            qseats.status.eq("가용"))
                    .rightJoin(qtickets)
                    .on(qtickets.id.eq(qscreen_seat.tickets.id),
                            qtickets.screen.id.eq(screen.getId()))
                    .where(qtickets.user.isNull(),
                            qscreen_seat.id.isNotNull())
                    .fetch();


            System.out.println(">> 이용 가능 좌석 <<");
            System.out.println("-".repeat(40));
            screen_seat2.stream().forEach(m->m.getSeats().printInfo());
            System.out.println("-".repeat(40));

            tx.commit();

        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
    }

    /* 7번 예매 */
    static void userTicketing(Tickets ticket, Users user) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        try {
            tx.begin();
            ticket.setUsers(user);
            em.merge(ticket);
            tx.commit();
        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
    }

    /* 9번 예매 정보 조회 */
    static void showTicket(Tickets ticket) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        try {
            tx.begin();
            JPAQueryFactory query = new JPAQueryFactory(em);

            QTickets qtickets = new QTickets("t");
            QScreen_Seat qscreen_seat = new QScreen_Seat("ss");

            List<Screen_Seat> screen_seat = query.selectFrom(qscreen_seat)
                            .join(qscreen_seat.tickets, qtickets)
                            .where(qtickets.id.eq(ticket.getId()))
                            .fetch();

            System.out.println(">>>>> 예매 정보 조회 <<<<<<");
            for (Screen_Seat tempScreenSeat : screen_seat) {
                System.out.println("영화이름/관이름/좌석/시작시간 : "+tempScreenSeat.getTickets().getScreen().getMovie().getName()
                        +"/"+tempScreenSeat.getTickets().getScreen().getTheater().getName()
                        +"/"+tempScreenSeat.getSeats().getColumn()+"행"+tempScreenSeat.getSeats().getColumn()+"열"
                        +"/"+tempScreenSeat.getTickets().getScreen().getStartTime());
            }
            tx.commit();

        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
    }

    /* 8번 예매 취소 */
    static void cancelTicking(Tickets ticket) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        try {
            tx.begin();
            ticket.setUser(null);
            em.merge(ticket);
            em.flush();
            tx.commit();
        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
    }

    /* 10번 사용자 삭제 */
    static void removeUser(EntityManager em, Users user) {
//      EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        try {
            //tx.begin();
            for (Tickets ticket : user.getTickets()) {
                ticket.setUser(null);
            }
            em.merge(user);
            user.setTickets(null);
            em.merge(user);
            em.remove(user);
            //tx.commit();
        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
    }

    /* 사전 데이터 생성*/
    static void createBeforeData()
    {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        try {
            tx.begin();


            //-- 영화 - 기생충, 연얘빠진 로맨스, 알라딘, 오펀 : 천사의 비밀 4개 --//
            SimpleDateFormat newDtFormat = new SimpleDateFormat("yyyy-MM-dd");

            Date date1 = newDtFormat.parse("2019-05-30");
            Movies movie1 = createMovie("기생충", date1, Genre.드라마, 131);
            Directors directors1 = createDirector("봉준호", 52, "대구광역시");
            Actors actor1 = createActor("송강호", 54, 180, "@Songkangho");
            Actors actor2 = createActor("이선균", 46, 180, "@kyun3333");
            Actors actor3 = createActor("박명훈", 46, 174, "@park_myung_hoon_528");
            Actors actor4 = createActor("정지소", 22, 163, "@mint_ziso");
            Actors actor5 = createActor("정현준", 10, 143, "@hyeonjun_mama");
            Movie_Worker movie_worker1 = createMovieWorker(Role_Type.감독, movie1, directors1);
            Movie_Worker movie_worker2 = createMovieWorker(Role_Type.주연, movie1, actor1);
            Movie_Worker movie_worker3 = createMovieWorker(Role_Type.주연, movie1, actor2);
            Movie_Worker movie_worker4 = createMovieWorker(Role_Type.조연, movie1, actor3);
            Movie_Worker movie_worker5 = createMovieWorker(Role_Type.조연, movie1, actor4);
            Movie_Worker movie_worker6 = createMovieWorker(Role_Type.조연, movie1, actor5);

            Date date2 = newDtFormat.parse("2021-11-24");
            Movies movie2 = createMovie("연애빠진 로맨스", date2, Genre.로맨스, 95);
            Directors directors2 = createDirector("정가영", 31, "대한민국");
            Actors actor6 = createActor("전종서", 27, 167, "@wjswhdtj94");
            Actors actor7 = createActor("손석구", 38, 178, "@sonsukku");
            Actors actor8 = createActor("공민정", 35, 169, "@greengreen_j");
            Actors actor9 = createActor("김슬기", 30, 157, "@s911010");
            Actors actor10 = createActor("배유람", 35, 175, "@gaeddac");
            Movie_Worker movie_worker7 = createMovieWorker(Role_Type.감독, movie2, directors2);
            Movie_Worker movie_worker8 = createMovieWorker(Role_Type.주연, movie2, actor6);
            Movie_Worker movie_worker9 = createMovieWorker(Role_Type.주연, movie2, actor7);
            Movie_Worker movie_worker10 = createMovieWorker(Role_Type.조연, movie2, actor1);
            Movie_Worker movie_worker11 = createMovieWorker(Role_Type.조연, movie2, actor9);
            Movie_Worker movie_worker12 = createMovieWorker(Role_Type.조연, movie2, actor10);

            Date date3 = newDtFormat.parse("2019-05-23");
            Movies movie3 = createMovie("알라딘", date3, Genre.모험, 128);
            Directors directors3 = createDirector("가이 리치", 53, "영국");
            Actors actor11 = createActor("나오미 스콧", 28, 167, "@naomigscott");
            Actors actor12 = createActor("윌 스미스", 53, 188, "@willsmith");
            Actors actor13 = createActor("마르완 켄자리", 38, 183, "@marwankenzari");
            Actors actor14 = createActor("네이비드 네가반", 53, 180, "@navidnegahban");
            Actors actor15 = createActor("나심 페드라드", 40, 163, "@nasimpedrad");
            Movie_Worker movie_worker13 = createMovieWorker(Role_Type.감독, movie3, directors3);
            Movie_Worker movie_worker14 = createMovieWorker(Role_Type.주연, movie3, actor11);
            Movie_Worker movie_worker15 = createMovieWorker(Role_Type.주연, movie3, actor12);
            Movie_Worker movie_worker16 = createMovieWorker(Role_Type.조연, movie3, actor13);
            Movie_Worker movie_worker17 = createMovieWorker(Role_Type.조연, movie3, actor14);
            Movie_Worker movie_worker18 = createMovieWorker(Role_Type.조연, movie3, actor15);

            Date date4 = newDtFormat.parse("2003-06-13");
            Movies movie4 = createMovie("오펀 : 천사의 비밀", date4, Genre.공포, 118);
            Directors directors4 = createDirector("자움 콜렛 세라", 47, "스페인");
            Actors actor16 = createActor("베라 파미가", 48, 166, "@verafarmiga");
            Actors actor17 = createActor("이사벨 퍼만", 24, 160, "@isabellefur");
            Actors actor18 = createActor("CCH 파운더", 69, 170, "@cchpounder");
            Actors actor19 = createActor("지미 베넷", 25, 165, "@jimmybennett");
            Actors actor20 = createActor("마고 마틴데일", 70, 166, "@margomartindale");
            Movie_Worker movie_worker19 = createMovieWorker(Role_Type.감독, movie4, directors4);
            Movie_Worker movie_worker20 = createMovieWorker(Role_Type.주연, movie4, actor16);
            Movie_Worker movie_worker21 = createMovieWorker(Role_Type.주연, movie4, actor17);
            Movie_Worker movie_worker22 = createMovieWorker(Role_Type.조연, movie4, actor18);
            Movie_Worker movie_worker23 = createMovieWorker(Role_Type.조연, movie4, actor19);
            Movie_Worker movie_worker24 = createMovieWorker(Role_Type.조연, movie4, actor20);

            // -- 상영관 및 좌석 : 2개의 상영관, 좌석은 각각 10개 -- //
            Theaters theater1 = createTheater("1상영관", 1);
            Seats seat1 = createSeat(1, 1, "가용", theater1);
            Seats seat2 = createSeat(1, 2, "가용", theater1);
            Seats seat3 = createSeat(1, 3, "가용", theater1);
            Seats seat4 = createSeat(1, 4, "가용", theater1);
            Seats seat5 = createSeat(1, 5, "가용", theater1);
            Seats seat6 = createSeat(2, 1, "가용", theater1);
            Seats seat7 = createSeat(2, 2, "가용", theater1);
            Seats seat8 = createSeat(2, 3, "가용", theater1);
            Seats seat9 = createSeat(2, 4, "불가용", theater1);
            Seats seat10 = createSeat(2, 5, "불가용", theater1);

            Theaters theater2 = createTheater("2상영관", 2);
            Seats seat11 = createSeat(1, 1, "가용", theater2);
            Seats seat12 = createSeat(1, 2, "가용", theater2);
            Seats seat13 = createSeat(1, 3, "가용", theater2);
            Seats seat14 = createSeat(1, 4, "가용", theater2);
            Seats seat15 = createSeat(1, 5, "가용", theater2);
            Seats seat16 = createSeat(2, 1, "가용", theater2);
            Seats seat17 = createSeat(2, 2, "가용", theater2);
            Seats seat18 = createSeat(2, 3, "가용", theater2);
            Seats seat19 = createSeat(2, 4, "가용", theater2);
            Seats seat20 = createSeat(2, 5, "가용", theater2);

            //----  12월 1일 하루당 3번의 영화 상영(screen), 1상영관은 기생충, 2상영관은 연얘빠진 로맨스 상영중 ---- //
            //  ticket은 각 상영당 10개
            SimpleDateFormat newDtFormat2 = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");
            Date date5 = newDtFormat2.parse("2021-12-01 08:00:00.000");
            Date date6 = newDtFormat2.parse("2021-12-01 10:11:00.000");
            Date date7 = newDtFormat2.parse("2021-12-01 12:00:00.000");
            Date date8 = newDtFormat2.parse("2021-12-01 14:11:00.000");
            Date date9 = newDtFormat2.parse("2021-12-01 18:00:00.000");
            Date date10 = newDtFormat2.parse("2021-12-01 20:11:00.000");
            System.out.println("data: " + date10);
            System.out.println("getTime: " + date10.getTime());
            Timestamp timestamp1 = new java.sql.Timestamp(date5.getTime());
            Timestamp timestamp2 = new java.sql.Timestamp(date6.getTime());
            Timestamp timestamp3 = new java.sql.Timestamp(date7.getTime());
            Timestamp timestamp4 = new java.sql.Timestamp(date8.getTime());
            Timestamp timestamp5 = new java.sql.Timestamp(date9.getTime());
            Timestamp timestamp6 = new java.sql.Timestamp(date10.getTime());

            // 기생충 - 12월 1일 상영 정보 및 티켓
            Screens screen1 = createScreen(theater1, movie1, timestamp1, timestamp2);
            Screens screen2 = createScreen(theater1, movie1, timestamp3, timestamp4);
            Screens screen3 = createScreen(theater1, movie1, timestamp5, timestamp6);
            Tickets ticket1 = createTicket(screen1);
            Tickets ticket2 = createTicket(screen1);
            Tickets ticket3 = createTicket(screen1);
            Tickets ticket4 = createTicket(screen1);
            Tickets ticket5 = createTicket(screen1);
            Tickets ticket6 = createTicket(screen1);
            Tickets ticket7 = createTicket(screen1);
            Tickets ticket8 = createTicket(screen1);
            Tickets ticket9 = createTicket(screen1);
            Tickets ticket10 = createTicket(screen1);
            Tickets ticket11 = createTicket(screen2);
            Tickets ticket12 = createTicket(screen2);
            Tickets ticket13 = createTicket(screen2);
            Tickets ticket14 = createTicket(screen2);
            Tickets ticket15 = createTicket(screen2);
            Tickets ticket16 = createTicket(screen2);
            Tickets ticket17 = createTicket(screen2);
            Tickets ticket18 = createTicket(screen2);
            Tickets ticket19 = createTicket(screen2);
            Tickets ticket20 = createTicket(screen2);
            Tickets ticket21 = createTicket(screen3);
            Tickets ticket22 = createTicket(screen3);
            Tickets ticket23 = createTicket(screen3);
            Tickets ticket24 = createTicket(screen3);
            Tickets ticket25 = createTicket(screen3);
            Tickets ticket26 = createTicket(screen3);
            Tickets ticket27 = createTicket(screen3);
            Tickets ticket28 = createTicket(screen3);
            Tickets ticket29 = createTicket(screen3);
            Tickets ticket30 = createTicket(screen3);
            screen1.addTicket(ticket1);
            screen1.addTicket(ticket2);
            screen1.addTicket(ticket3);
            screen1.addTicket(ticket4);
            screen1.addTicket(ticket5);
            screen1.addTicket(ticket6);
            screen1.addTicket(ticket7);
            screen1.addTicket(ticket8);
            screen1.addTicket(ticket9);
            screen1.addTicket(ticket10);
            em.merge(screen1);
            screen2.addTicket(ticket11);
            screen2.addTicket(ticket12);
            screen2.addTicket(ticket13);
            screen2.addTicket(ticket14);
            screen2.addTicket(ticket15);
            screen2.addTicket(ticket16);
            screen2.addTicket(ticket17);
            screen2.addTicket(ticket18);
            screen2.addTicket(ticket19);
            screen2.addTicket(ticket20);
            em.merge(screen2);
            screen3.addTicket(ticket21);
            screen3.addTicket(ticket22);
            screen3.addTicket(ticket23);
            screen3.addTicket(ticket24);
            screen3.addTicket(ticket25);
            screen3.addTicket(ticket26);
            screen3.addTicket(ticket27);
            screen3.addTicket(ticket28);
            screen3.addTicket(ticket29);
            screen3.addTicket(ticket30);
            em.merge(screen3);
            createScreenSeat(seat1, ticket1);
            createScreenSeat(seat2, ticket2);
            createScreenSeat(seat3, ticket3);
            createScreenSeat(seat4, ticket4);
            createScreenSeat(seat5, ticket5);
            createScreenSeat(seat6, ticket6);
            createScreenSeat(seat7, ticket7);
            createScreenSeat(seat8, ticket8);
            createScreenSeat(seat9, ticket9);
            createScreenSeat(seat10, ticket10);
            createScreenSeat(seat1, ticket11);
            createScreenSeat(seat2, ticket12);
            createScreenSeat(seat3, ticket13);
            createScreenSeat(seat4, ticket14);
            createScreenSeat(seat5, ticket15);
            createScreenSeat(seat6, ticket16);
            createScreenSeat(seat7, ticket17);
            createScreenSeat(seat8, ticket18);
            createScreenSeat(seat9, ticket19);
            createScreenSeat(seat10, ticket20);
            createScreenSeat(seat1, ticket21);
            createScreenSeat(seat2, ticket22);
            createScreenSeat(seat3, ticket23);
            createScreenSeat(seat4, ticket24);
            createScreenSeat(seat5, ticket25);
            createScreenSeat(seat6, ticket26);
            createScreenSeat(seat7, ticket27);
            createScreenSeat(seat8, ticket28);
            createScreenSeat(seat9, ticket29);
            createScreenSeat(seat10, ticket30);

            // 연얘빠진로맨스 - 12월 1일 상영 정보 및 티켓
            Screens screen4 = createScreen(theater2, movie2, timestamp1, timestamp2);
            Screens screen5 = createScreen(theater2, movie2, timestamp3, timestamp4);
            Screens screen6 = createScreen(theater2, movie2, timestamp5, timestamp6);
            Tickets ticket31 = createTicket(screen4);
            Tickets ticket32 = createTicket(screen4);
            Tickets ticket33 = createTicket(screen4);
            Tickets ticket34 = createTicket(screen4);
            Tickets ticket35 = createTicket(screen4);
            Tickets ticket36 = createTicket(screen4);
            Tickets ticket37 = createTicket(screen4);
            Tickets ticket38 = createTicket(screen4);
            Tickets ticket39 = createTicket(screen4);
            Tickets ticket40 = createTicket(screen4);
            Tickets ticket41 = createTicket(screen4);
            Tickets ticket42 = createTicket(screen4);
            Tickets ticket43 = createTicket(screen4);
            Tickets ticket44 = createTicket(screen4);
            Tickets ticket45 = createTicket(screen4);
            Tickets ticket46 = createTicket(screen4);
            Tickets ticket47 = createTicket(screen4);
            Tickets ticket48 = createTicket(screen4);
            Tickets ticket49 = createTicket(screen4);
            Tickets ticket50 = createTicket(screen4);
            Tickets ticket51 = createTicket(screen4);
            Tickets ticket52 = createTicket(screen4);
            Tickets ticket53 = createTicket(screen4);
            Tickets ticket54 = createTicket(screen4);
            Tickets ticket55 = createTicket(screen4);
            Tickets ticket56 = createTicket(screen4);
            Tickets ticket57 = createTicket(screen4);
            Tickets ticket58 = createTicket(screen4);
            Tickets ticket59 = createTicket(screen4);
            Tickets ticket60 = createTicket(screen4);
            screen4.addTicket(ticket31);
            screen4.addTicket(ticket32);
            screen4.addTicket(ticket33);
            screen4.addTicket(ticket34);
            screen4.addTicket(ticket35);
            screen4.addTicket(ticket36);
            screen4.addTicket(ticket37);
            screen4.addTicket(ticket38);
            screen4.addTicket(ticket39);
            screen4.addTicket(ticket40);
            em.merge(screen4);
            screen5.addTicket(ticket41);
            screen5.addTicket(ticket42);
            screen5.addTicket(ticket43);
            screen5.addTicket(ticket44);
            screen5.addTicket(ticket45);
            screen5.addTicket(ticket46);
            screen5.addTicket(ticket47);
            screen5.addTicket(ticket48);
            screen5.addTicket(ticket49);
            screen5.addTicket(ticket50);
            em.merge(screen5);
            screen6.addTicket(ticket51);
            screen6.addTicket(ticket52);
            screen6.addTicket(ticket53);
            screen6.addTicket(ticket54);
            screen6.addTicket(ticket55);
            screen6.addTicket(ticket56);
            screen6.addTicket(ticket57);
            screen6.addTicket(ticket58);
            screen6.addTicket(ticket59);
            screen6.addTicket(ticket60);
            em.merge(screen6);
            createScreenSeat(seat1, ticket31);
            createScreenSeat(seat2, ticket32);
            createScreenSeat(seat3, ticket33);
            createScreenSeat(seat4, ticket34);
            createScreenSeat(seat5, ticket35);
            createScreenSeat(seat6, ticket36);
            createScreenSeat(seat7, ticket37);
            createScreenSeat(seat8, ticket38);
            createScreenSeat(seat9, ticket39);
            createScreenSeat(seat10, ticket40);
            createScreenSeat(seat1, ticket41);
            createScreenSeat(seat2, ticket42);
            createScreenSeat(seat3, ticket43);
            createScreenSeat(seat4, ticket44);
            createScreenSeat(seat5, ticket45);
            createScreenSeat(seat6, ticket46);
            createScreenSeat(seat7, ticket47);
            createScreenSeat(seat8, ticket48);
            createScreenSeat(seat9, ticket49);
            createScreenSeat(seat10, ticket50);
            createScreenSeat(seat1, ticket51);
            createScreenSeat(seat2, ticket52);
            createScreenSeat(seat3, ticket53);
            createScreenSeat(seat4, ticket54);
            createScreenSeat(seat5, ticket55);
            createScreenSeat(seat6, ticket56);
            createScreenSeat(seat7, ticket57);
            createScreenSeat(seat8, ticket58);
            createScreenSeat(seat9, ticket59);
            createScreenSeat(seat10, ticket60);

            // 사용자
            Users user1 = createUser("이수진", 22, "구미", "형곡동", "ASI|KR|KS010|GUMI");
            Users user2 = createUser("최연서", 22, "대구", "달서구", "ASI|KR|KS006|TAEGU");

            // 예매
            userTicketing(ticket1, user1);
            userTicketing(ticket2, user2);
            tx.commit();
        } catch (Exception e) {
            tx.rollback();
        } finally {
            em.close();
        }
    }
}
