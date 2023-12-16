#
# This is a Shiny web application. You can run the application by clicking
# the 'Run App' button above.
#
# Find out more about building applications with Shiny here:
#
#    http://shiny.rstudio.com/
#

library(shiny)
library(tidyverse)
library(plotly)
library(car)
library(gridExtra)
library(qqplotr)
library(robustbase)

# Define UI for application that draws a histogram
ui <- fluidPage(

    # Application title
    titlePanel("Central Limit Theorem", windowTitle = "Central Limit Theorem"),

    # Sidebar with a slider input for distributions and sizes
    sidebarLayout(
        sidebarPanel(
          wellPanel(
            radioButtons("dist", "Population Distribution:",
                         c("Normal" = "rnorm",
                           "Uniform" = "runif",
                           "Right Skewed" = "rlnorm",
                           "Left Skewed" = "rbeta",
                           "Bimodal" = "rbimd",
                           "Cauchy" = "rcauchy"
                           ),
                         selected = "rnorm"),
            
            sliderInput("n",
                        "Sample Size:",
                        min = 5,
                        max = 500,
                        value = 5,
                        step = 5),
          
          
          
            sliderInput("k",
                        "Number of samples:",
                        min = 10,
                        max = 500,
                        value = 10,
                        step=10),
            
            
            textInput("name","Your Name + Date:", value="")
            
          ),
            helpText("Author: Dr. Jiacheng Cai, Salisbury University"),
            helpText("Version: 202307v00")
            
        ),

        # Show a plot of the generated distribution
        mainPanel(
          tabsetPanel(
            type="tabs",
            
            tabPanel(
              title="Population Distribution",
              plotlyOutput("popDist", height="500px")
              
            ),
            
            tabPanel(
              title="Plots of First Eight Samples",
              br(),
              plotlyOutput("sample.dist", height = "600px"),
              #  Number of samples text ----
              #div(h3(textOutput("num.samples")), align = "center"),
              br()
            ),
            
            tabPanel(
              title="Sample Details",
              DT::dataTableOutput("samplesTable")
            ),
            
            
            tabPanel(
              title="Sampling Distribution - Sample Mean",
              fluidRow(
                splitLayout(cellWidths = c("45%", "45%"),
                plotlyOutput("sampling.dist1", height="500px"),
                plotOutput("sampling.dist1.qq", height="500px"),
                )
                
              )
            ),
            
            
            tabPanel(
              title="Sampling Distribution - Sample Median",
              fluidRow(
                splitLayout(cellWidths = c("45%", "45%"),
                            plotlyOutput("sampling.dist2", height="500px"),
                            plotOutput("sampling.dist2.qq", height="500px"),
                )
                
              )
            ),
            
            
            tabPanel(
              title="About"
              
            )
            

          )
        )
    )
)

# Define server logic required to draw a histogram
server <- function(input, output) {
  
    rand_gen <- function(dist,n){
    
    vals = NULL
    
    if(dist == "rnorm"){
      vals = rnorm(n,0,1)
    }
    else if (dist =="runif"){
      vals = runif(n,0,1)
    }
    else if (dist =="rlnorm"){
      vals = rlnorm(n,0,0.5)
    }
    else if (dist =="rbeta"){
      vals = rbeta(n,5,1.5)
    } 
    else if (dist =="rcauchy"){
      vals = rcauchy(n,0,1)
    }
    else if (dist =="rbimd"){
      flag = rbinom(n,1,0.5)
      for (i in 1:n){
        if (flag[i] == 0){
          vals[i] = rnorm(1,-2,sd=1)
        }
        else if (flag[i]==1){
          vals[i] = rnorm(1,3,sd=2)
        }
      }
    }
    
    return(vals)
    
    }
  
    rep_rand_gen = repeatable(rand_gen)
  
    
    parent = reactive({
    
      return(rep_rand_gen(input$dist,3e5))
    

    })
    
    samples = reactive({
      
      pop = parent()

      return(replicate(input$k,sample(pop,input$n,replace=TRUE)))
      
    })
    
    
    
    

    output$popDist <- renderPlotly({
        # 
      
        pop = parent()
        
        m_pop = round(mean(pop),3)
        sd_pop = round(sd(pop),3)
        md_pop = round(median(pop),3)
        
        
        pop = tibble(samples = pop)
        
        
        if (input$dist=="rnorm"){
          ggplotly(
            ggplot(data=pop, aes(x = samples,y=..density..))+
              geom_histogram(bins = 45, color = "black", fill="blue")+
              labs(title=paste("Population Distribution: Normal - ",input$name), x="x")+
              annotate("text",x=2.5,y=0.35,
                     label = paste("mean of x", "=", bquote(.(m_pop)),
                                   "\n", "median of x", "=", bquote(.(md_pop)),
                                   "\n", "SD of x", "=", bquote(.(sd_pop))),
                     color = "black", size = 5)+
              theme(text = element_text(size = 15)) 
          )
        }
        
        else if (input$dist=="runif"){
          ggplotly(
            ggplot(data=pop, aes(x = samples,y=..density..))+
              geom_histogram(bins = 45, color = "black", fill="blue")+
              scale_y_continuous(expand = expand_scale(mult = c(0, .3))) +
              labs(title=paste("Population Distribution: Uniform - ",input$name), x="x")+
              annotate("text",x=0.7,y=1.35,
                     label = paste("mean of x", "=", bquote(.(m_pop)),
                                   "\n", "median of x", "=", bquote(.(md_pop)),
                                   "\n", "SD of x", "=", bquote(.(sd_pop))),
                     color = "black", size = 5)+
              theme(text = element_text(size = 15)) 
          )
        }
        
        else if (input$dist=="rbimd"){
          ggplotly(
            ggplot(data=pop, aes(x = samples,y=..density..))+
              geom_histogram(bins = 45, color = "black", fill="blue")+
              labs(title=paste("Population Distribution: Bimodal - ",input$name), x="x")+
              annotate("text",x=7,y=0.15,
                     label = paste("mean of x", "=", bquote(.(m_pop)),
                                   "\n", "median of x", "=", bquote(.(md_pop)),
                                   "\n", "SD of x", "=", bquote(.(sd_pop))),
                     color = "black", size = 5)+
              theme(text = element_text(size = 15)) 
          )
        }
        
        else if (input$dist=="rlnorm"){
          ggplotly(
            ggplot(data=pop, aes(x = samples,y=..density..))+
              geom_histogram(bins = 45, color = "black", fill="blue")+
              labs(title=paste("Population Distribution: Right Skewed - ",input$name), x="x")+
              annotate("text",x=4,y=0.5,
                     label = paste("mean of x", "=", bquote(.(m_pop)),
                                   "\n", "median of x", "=", bquote(.(md_pop)),
                                   "\n", "SD of x", "=", bquote(.(sd_pop))),
                     color = "black", size = 5)+
              theme(text = element_text(size = 15)) 
          )
        }
        
        else if (input$dist=="rbeta"){
          ggplotly(
            ggplot(data=pop, aes(x = samples,y=..density..))+
              geom_histogram(bins = 45, color = "black", fill="blue")+
              labs(title=paste("Population Distribution: Left Skewed - ",input$name), x="x")+
              annotate("text",x=0.25,y=2.5,
                     label = paste("mean of x", "=", bquote(.(m_pop)),
                                   "\n", "median of x", "=", bquote(.(md_pop)),
                                   "\n", "SD of x", "=", bquote(.(sd_pop))),
                     color = "black", size = 5)+
              theme(text = element_text(size = 15)) 
          )
        }
        
        else if (input$dist=="rcauchy"){
          ggplotly(
            ggplot(data=pop, aes(x = samples,y=..density..))+
              geom_histogram(bins = 45, color = "black", fill="blue")+
              xlim(-40,40)+
              labs(title=paste("Population Distribution: Cauchy - ",input$name), x="x")+
              annotate("text",x=-20,y=0.2,
                     label = paste("mean of x", "=", "undefine",
                                   "\n", "median of x", "=", bquote(.(md_pop)),
                                   "\n", "SD of x", "=", "undefine"),
                     color = "black", size = 5)+
              theme(text = element_text(size = 15)) 
          )
        }
      
    })
    
    
    
    output$samplesTable<-DT::renderDataTable({
      
      y<-samples()
      
      y<-round(y,3)
      
      cnames <- c()
      rnames <- c()
      
      mean_sample <- c()
      median_sample <- c()
      sd_sample <- c()
      
      if (input$dist=="rnorm"){
        samptabtitle=paste("Table of Samples from Normal Population - ",input$name)
      }
      else if (input$dist=="runif"){
        samptabtitle=paste("Table of Samples from Uniform Population - ",input$name)
      }
      else if (input$dist=="rbimd"){
        samptabtitle=paste("Table of Samples from Bimodal Population - ",input$name)
      }
      else if (input$dist=="rlnorm"){
        samptabtitle=paste("Table of Samples from Right Skewed Population - ",input$name)
      }
      else if (input$dist=="rbeta"){
        samptabtitle=paste("Table of Samples from Left Skewed Population - ",input$name)
      }
      else if (input$dist=="rcauchy"){
        samptabtitle=paste("Table of Samples from Cauchy Population - ",input$name)
      }
      
      for (i in 1:input$k){
        cnames[i] <- paste("Sample ",as.character(i))
        mean_sample[i] <- round(mean(y[,i]),3)
        median_sample[i] <- round(median(y[,i]),3)
        sd_sample[i] <- round(sd(y[,i]),3)
      }
      
      for (i in 4:(input$n+3)){
        rnames[i] <- paste("Value ", as.character(i-3)) 
      }
      
      rnames[1] <- "Sample Mean"
      rnames[2] <- "Sample Median"
      rnames[3] <- "Sample StDev"
      
      sample_output <- rbind(sd_sample,y)
      sample_output <- rbind(median_sample,sample_output)
      sample_output <- rbind(mean_sample,sample_output)
      
      colnames(sample_output) <- cnames
      rownames(sample_output) <- rnames
      
      DT::datatable(sample_output,
        options = list(
          paging=FALSE,
          scrollX=TRUE,
          scrollY=TRUE,
          dom = 'Bfrtip',
          buttons = c('csv', 'excel')
        ),
        caption = samptabtitle,
        rownames = TRUE,
        extensions = 'Buttons'
      )
      
      
    })
    
    
    
    output$sample.dist = renderPlotly({
      
      y = samples()
      x = samples() %>% as_tibble()
      
      if (input$dist=="rnorm"){
        sampplottitle=paste("Plot of 8 Samples from Normal Population - ",input$name)
      }
      else if (input$dist=="runif"){
        sampplottitle=paste("Plot of 8 Samples from Uniform Population - ",input$name)
      }
      else if (input$dist=="rbimd"){
        sampplottitle=paste("Plot of 8 Samples from Bimodal Population - ",input$name)
      }
      else if (input$dist=="rlnorm"){
        sampplottitle=paste("Plot of 8 Samples from Right Skewed Population - ",input$name)
      }
      else if (input$dist=="rbeta"){
        sampplottitle=paste("Plot of 8 Samples from Left Skewed Population - ",input$name)
      }
      else if (input$dist=="rcauchy"){
        sampplottitle=paste("Plot of 8 Samples from Cauchy Population - ",input$name)
      }
      
      
      
      plots = list(rep(NA, 8))
      
      for(i in 1:8){
        
        mean = round(mean(y[,i]), 2)
        median = round(median(y[,i]), 2)
        sd = round(sd(y[,i]), 2)
        
        x_range = max(y[,i]) - min(y[,i])
        pdens = density(y[,i])
        
        x_pos = ifelse(input$dist == "rbeta", min(y[,i]) + 0.12*x_range, 
                       max(y[,i]) - 0.12*x_range)
        
        plots[[i]] = ggplot(x, aes_string(x = paste0("V", i))) +
          geom_dotplot(alpha = 0.8, dotsize = 0.1) +
          labs(title = paste("Sample", i), x = "", y = "") +
          theme_light(base_size = 13) +
          annotate("text", x = x_pos, y = 1.5,
                   label = paste("x_bar", "=", bquote(.(mean)),
                                 "\n", "Median", "=", bquote(.(median)),
                                 "\n", "SD", "=", bquote(.(sd))),
                   color = "black", size = 2) +
          scale_y_continuous(limits = c(0,2), breaks = NULL) +
          theme(plot.title = element_text(hjust = 0.5),
                panel.grid.major = element_blank(),
                panel.grid.minor = element_blank())
        
      }
      
      subplot(plots[[1]], plots[[2]], plots[[3]], plots[[4]], plots[[5]],
                   plots[[6]], plots[[7]], plots[[8]], nrows = 2,margin = 0.04, widths=c(0.2,0.25,0.25,0.2)) %>%
        layout(title=sampplottitle)
      
      #grid.arrange(plots[[1]], plots[[2]], plots[[3]], plots[[4]], plots[[5]],
                   #plots[[6]], plots[[7]], plots[[8]], ncol = 4)
    })
    
    
    
    output$sampling.dist1 = renderPlotly({
      
      n = input$n
      k = input$k
      
      pop = parent()
      
      m_pop =  round(mean(pop),3)
      sd_pop = round(sd(pop),3)
      
      
      ndist = tibble(means = colMeans(samples()))
      
      m_samp =  round(mean(ndist$means),3)
      sd_samp = round(sd(ndist$means),3)
      
      ndens = density(ndist$means)
      nhist = hist(ndist$means, plot=FALSE)
      
      x_range = max(ndist$means) - min(ndist$means)
      
      y_pos = max(ndens$y) - 0.12*max(ndens$y)
      x_pos = ifelse(m_samp > 0, min(ndist$means) + 0.1*x_range, 
                     max(ndist$means) - 0.1*x_range)
      
      
      if (input$dist=="rnorm"){
        sampdisttitle=paste("Sampling Distribution of Sample Means from Normal Population - ",input$name)
      }
      else if (input$dist=="runif"){
        sampdisttitle=paste("Sampling Distribution of Sample Means from Uniform Population - ",input$name)
      }
      else if (input$dist=="rbimd"){
        sampdisttitle=paste("Sampling Distribution of Sample Means from Bimodal Population - ",input$name)
      }
      else if (input$dist=="rlnorm"){
        sampdisttitle=paste("Sampling Distribution of Sample Means from Right Skewed Population - ",input$name)
      }
      else if (input$dist=="rbeta"){
        sampdisttitle=paste("Sampling Distribution of Sample Means from Left Skewed Population - ",input$name)
      }
      else if (input$dist=="rcauchy"){
        sampdisttitle=paste("Sampling Distribution of Sample Means from Cauchy Population - ",input$name)
      }
      
      p = ggplot(data = ndist, aes(x = means, y = ..density..)) +
        geom_histogram(bins = 20, color = "white", fill = "blue") +
        stat_density(geom = "line", color = "blue", size = 1) +
        labs(title = sampdisttitle,
             x = "Sample means",
             y = "") +
        annotate("text", x = x_pos, y = y_pos,
                 label = paste("mean of x_bar", "=", bquote(.(m_samp)),
                               "\n", "SD of x_bar", "=", bquote(.(sd_samp)),
                               "\n", "Sample Size","=",bquote(.(n)),
                               "\n", "Number of Samples","=",bquote(.(k)),
                               "\n","mean of x", "=", bquote(.(m_pop)),
                               "\n","SD of x/sqrt(n)", "=", bquote(.(round(sd_pop/sqrt(n),3)))),
                 color = "black", size = 3) +
        theme_light(base_size = 19) +
        theme(plot.title = element_text(hjust = 0.5, size=10),
              axis.text = element_text(size=10),
              text = element_text(size=10),
              panel.grid.major = element_blank(),
              panel.grid.minor = element_blank())
      
      ggplotly(p)
      
      
    })
    
    
    output$sampling.dist1.qq = renderPlot({
      
      n = input$n
      k = input$k
      
      pop = parent()
      
      m_pop =  round(mean(pop),3)
      sd_pop = round(sd(pop),3)
      
      
      ndist = tibble(means = colMeans(samples()))
      
      
      
      
      if (input$dist=="rnorm"){
        sampdisttitle=paste("QQ plot of Sample Means from Normal Population - ",input$name)
      }
      else if (input$dist=="runif"){
        sampdisttitle=paste("QQ plot of Sample Means from Uniform Population - ",input$name)
      }
      else if (input$dist=="rbimd"){
        sampdisttitle=paste("QQ plot of Sample Means from Bimodal Population - ",input$name)
      }
      else if (input$dist=="rlnorm"){
        sampdisttitle=paste("QQ plot of Sample Means from Right Skewed Population - ",input$name)
      }
      else if (input$dist=="rbeta"){
        sampdisttitle=paste("QQ plot of Sample Means from Left Skewed Population - ",input$name)
      }
      else if (input$dist=="rcauchy"){
        sampdisttitle=paste("QQ plot of Sample Means from Cauchy Population - ",input$name)
      }
      
      p = ggplot(data = ndist, aes(sample=means))+
        stat_qq_band()+stat_qq_point()+stat_qq_line()+
        labs(title = sampdisttitle)+
        theme_light(base_size = 19) +
        theme(plot.title = element_text(hjust = 0.5, size=15),
              axis.text = element_text(size=15),
              text = element_text(size=15))
      
      p
      
      
    })
    
    
    output$sampling.dist2 = renderPlotly({
      
      n = input$n
      k = input$k
      
      pop = parent()
      
      md_pop =  round(median(pop),3)
      sd_pop = round(sd(pop),3)
      
      
      ndist = tibble(medians = colMedians(samples()))
      
      md_samp =  round(mean(ndist$medians),3)
      sd_samp = round(sd(ndist$medians),3)
      
      ndens = density(ndist$medians)
      nhist = hist(ndist$medians, plot=FALSE)
      
      x_range = max(ndist$medians) - min(ndist$medians)
      
      y_pos = max(ndens$y) - 0.12*max(ndens$y)
      x_pos = ifelse(md_samp > 0, min(ndist$medians) + 0.1*x_range, 
                     max(ndist$medians) - 0.1*x_range)
      
      
      if (input$dist=="rnorm"){
        sampdisttitle=paste("Sampling Distribution of Sample Medians from Normal Population - ",input$name)
      }
      else if (input$dist=="runif"){
        sampdisttitle=paste("Sampling Distribution of Sample Medians from Uniform Population - ",input$name)
      }
      else if (input$dist=="rbimd"){
        sampdisttitle=paste("Sampling Distribution of Sample Medians from Bimodal Population - ",input$name)
      }
      else if (input$dist=="rlnorm"){
        sampdisttitle=paste("Sampling Distribution of Sample Medians from Right Skewed Population - ",input$name)
      }
      else if (input$dist=="rbeta"){
        sampdisttitle=paste("Sampling Distribution of Sample Medians from Left Skewed Population - ",input$name)
      }
      else if (input$dist=="rcauchy"){
        sampdisttitle=paste("Sampling Distribution of Sample Medians from Cauchy Population - ",input$name)
      }
      
      p = ggplot(data = ndist, aes(x = medians, y = ..density..)) +
        geom_histogram(bins = 20, color = "white", fill = "blue") +
        stat_density(geom = "line", color = "blue", size = 1) +
        labs(title = sampdisttitle,
             x = "Sample medians",
             y = "") +
        annotate("text", x = x_pos, y = y_pos,
                 label = paste("mean of samp_median", "=", bquote(.(md_samp)),
                               "\n", "SD of samp_median", "=", bquote(.(sd_samp)),
                               "\n", "Sample Size","=",bquote(.(n)),
                               "\n", "Number of Samples","=",bquote(.(k)),
                               "\n","median of x", "=", bquote(.(md_pop)),
                               "\n","1/sqrt(n)", "=", bquote(.(round(1/sqrt(n),3))),
                               "\n","Ratio of 2nd and 6th line", "=",bquote(.(round(sd_samp*sqrt(n),3)))),
                 color = "black", size = 3) +
        theme_light(base_size = 19) +
        theme(plot.title = element_text(hjust = 0.5, size=10),
              axis.text = element_text(size=10),
              text = element_text(size=10),
              panel.grid.major = element_blank(),
              panel.grid.minor = element_blank())
      
      ggplotly(p)
      
      
    })
    
    
    output$sampling.dist2.qq = renderPlot({
      
      n = input$n
      k = input$k
      
      pop = parent()
      
      md_pop =  round(median(pop),3)
      sd_pop = round(sd(pop),3)
      
      
      ndist = tibble(medians = colMedians(samples()))
      
      
      
      
      if (input$dist=="rnorm"){
        sampdisttitle=paste("QQ plot of Sample Medians from Normal Population - ",input$name)
      }
      else if (input$dist=="runif"){
        sampdisttitle=paste("QQ plot of Sample Medians from Uniform Population - ",input$name)
      }
      else if (input$dist=="rbimd"){
        sampdisttitle=paste("QQ plot of Sample Medians from Bimodal Population - ",input$name)
      }
      else if (input$dist=="rlnorm"){
        sampdisttitle=paste("QQ plot of Sample Medians from Right Skewed Population - ",input$name)
      }
      else if (input$dist=="rbeta"){
        sampdisttitle=paste("QQ plot of Sample Medians from Left Skewed Population - ",input$name)
      }
      else if (input$dist=="rcauchy"){
        sampdisttitle=paste("QQ plot of Sample Medians from Cauchy Population - ",input$name)
      }
      
      p = ggplot(data = ndist, aes(sample=medians))+
        stat_qq_band()+stat_qq_point()+stat_qq_line()+
        labs(title = sampdisttitle)+
        theme_light(base_size = 19) +
        theme(plot.title = element_text(hjust = 0.5, size=15),
              axis.text = element_text(size=15),
              text = element_text(size=15))
      
      p
      
      
    })
    
    
    
    
    
}

# Run the application 
shinyApp(ui = ui, server = server)
