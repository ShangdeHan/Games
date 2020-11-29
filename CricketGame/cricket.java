package hw2;
import api.Defaults;

import api.Outcome;
public class CricketGame {
    private int BowlsPerOver;
    private int OversPerInnings;
    private int TotalInnings;
    private int NumPlayers;
    private int batsmanscores;
    private int bowelscores;
    private int overcount;
    private int bowlcount;
    private int playersOut;
    private int innings;
    private boolean inplay;
    private boolean batsmanrunning;


    public  CricketGame ()
    {
        BowlsPerOver = Defaults.DEFAULT_BOWLS_PER_OVER;
        OversPerInnings = Defaults.DEFAULT_OVERS_PER_INNINGS;
        NumPlayers = Defaults.DEFAULT_NUM_INNINGS;
        playersOut = Defaults.DEFAULT_NUM_PLAYERS;
    }

    public CricketGame(int givenBowlsPerOver, int givenOversPerInnings, int givenTotalInnings, int givenNumPlayers) {
        BowlsPerOver = givenBowlsPerOver;
        OversPerInnings = givenOversPerInnings;
        NumPlayers = givenNumPlayers;
        playersOut = 0;
        innings = 0;
        inplay = false;

        if(givenTotalInnings%2!=0)
        {
            TotalInnings = givenTotalInnings +1;
        }
        else
        {
            TotalInnings = givenTotalInnings;
        }
    }
    public void bowl(Outcome outcome)
    {
        if (outcome == Outcome.WICKET)
        {
            playersOut += 1;
            bowlcount += 1;
            if (innings % 2 == 0)
            {
                batsmanscores += 1;
            }
            if (innings % 2 != 0)
            {
                bowelscores += 1;
            }
            if (bowlcount == BowlsPerOver)
            {
                bowlcount = 0;
                overcount += 1;
            }
            if (overcount == OversPerInnings)
            {
                overcount = 0;
                innings += 1;
            }
            if (NumPlayers - playersOut == 1)
            {
                innings += 1;
                bowlcount = 0;
                overcount = 0;
            }
            if (playersOut == NumPlayers)
            {
                playersOut = 1;
            }
        }
        if (outcome == Outcome.LBW)
        {
            playersOut += 1;
            bowlcount += 1;
            if (innings % 2 == 0)
            {
                batsmanscores += 1;
            }
            if (innings % 2 != 0)
            {
                bowelscores += 1;
            }
            if (bowlcount == BowlsPerOver)
            {
                bowlcount = 0;
                overcount += 1;
            }
            if (overcount == OversPerInnings)
            {
                overcount = 0;
                innings += 1;
            }
            if (NumPlayers - playersOut == 1)
            {
                innings += 1;
                bowlcount = 0;
                overcount = 0;
            }
            if (playersOut == NumPlayers)
            {
                playersOut = 1;
            }

        }
        if (outcome == Outcome.CAUGHT_FLY)
        {
            playersOut += 1;
            if (innings % 2 == 0)
            {
                batsmanscores += 1;
            }
            if (innings % 2 != 0)
            {
                bowelscores += 1;
            }
            bowlcount += 1;
            if (bowlcount == BowlsPerOver)
            {
                bowlcount = 0;
                overcount += 1;
            }
            if (overcount == OversPerInnings)
            {
                overcount = 0;
                innings += 1;
            }
            if (NumPlayers - playersOut == 1)
            {
                innings += 1;
                bowlcount = 0;
                overcount = 0;
            }
            if (playersOut == NumPlayers)
            {
                playersOut = 1;
            }

        }
        if (outcome == Outcome.WIDE)
        {
            if (innings % 2 == 0)
            {
                batsmanscores += 1;
            }
            if (innings % 2 != 0)
            {
                bowelscores += 1;
            }
            bowlcount += 1;
            if (bowlcount == BowlsPerOver)
            {
                bowlcount = 0;
                overcount += 1;
            }
            if (overcount == OversPerInnings)
            {
                overcount = 0;
                innings += 1;
            }
        }
        if (outcome == Outcome.NO_BALL)
        {
            if (innings % 2 == 0)
            {
                batsmanscores += 1;
            }
            if (innings % 2 != 0)
            {
                bowelscores += 1;
            }
            bowlcount += 1;
            if (bowlcount == BowlsPerOver)
            {
                bowlcount = 0;
                overcount += 1;
            }
            if (overcount == OversPerInnings)
            {
                overcount = 0;
                innings += 1;
            }


        }
        if (outcome == Outcome.BOUNDARY_SIX)
        {
            bowlcount += 1;

            if (innings % 2 == 0)
            {
                batsmanscores += 1;
            }
            if (innings % 2 != 0)
            {
                bowelscores += 1;
            }
            if (bowlcount == BowlsPerOver)
            {
                bowlcount = 0;
                overcount += 1;
            }
            if (overcount == OversPerInnings)
            {
                overcount = 0;
                innings += 1;
            }


        }
        if (outcome == Outcome.BOUNDARY_FOUR)
        {
            bowlcount += 1;
            if (innings % 2 == 0)
            {
                batsmanscores += 1;
            }
            if (innings % 2 != 0)
            {
                bowelscores += 1;
            }
            if (bowlcount == BowlsPerOver)
            {
                bowlcount = 0;
                overcount += 1;
            }
            if (overcount == OversPerInnings)
            {
                overcount = 0;
                innings += 1;
            }


        }
        if (outcome == Outcome.HIT)
        {
            if (innings % 2 == 0)
            {
                batsmanscores += 1;
            }
            if (innings % 2 != 0)
            {
                bowelscores += 1;
            }
            inplay = true;
            bowlcount += 1;
            if (bowlcount == BowlsPerOver)
            {
                bowlcount = 0;
                overcount += 1;
            }
            if (overcount == OversPerInnings)
            {
                overcount = 0;
                innings += 1;
            }
        }
    }

    public int getScore(boolean battingSide)
    {
        if(battingSide == true)
        {
            return batsmanscores;
        }
        else
        {
            return bowelscores;
        }
    }
    public int getBowlCount()
    {
        return bowlcount;
    }
    public int getOverCount()
    {
        return overcount;
    }
    public int getOuts()
    {
        return playersOut;
    }
    public boolean isGameEnded()
    {
        if ((innings > TotalInnings) ||(NumPlayers < playersOut +1))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    public int whichSideIsBatting()
    {
        if (innings % 2 == 0)
        {
            return 0;
        }else
        {
            return 1;
        }
    }
    public int getCompletedInnings()
    {

        return innings;
    }
    public boolean isInPlay()
    {
        if (inplay == true)
        {
            return true;
        }else
        {
            return false;
        }
    }
    public boolean isRunning()
    {
        return batsmanrunning;
    }

    public void tryRun()
    {
        if (inplay == true) {
            if (batsmanrunning == false)
            {
                batsmanrunning = true;
            }else
            {
                batsmanscores += 1;
            }
        }
    }
    public void safe()
    {
        if (inplay == true)
        {
            inplay = false;
            if (batsmanrunning == true)
            {
                batsmanscores += 1;
                batsmanrunning = false;
            }
        }
    }
    public void runOut()
    {
        if ((batsmanrunning == true) && (innings <= TotalInnings));
        playersOut += 1;
    }


}

